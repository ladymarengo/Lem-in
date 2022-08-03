use std::{
    cmp::{max, min},
    collections::HashMap,
    env,
    fs::read_to_string,
};

use bevy::{prelude::*, core::FixedTimestep};
use libm::{atan2, hypot};
use regex::Regex;
const WIDTH: f32 = 1800.0;
const HEIGHT: f32 = 1200.0;
const OFFSET: f32 = 20.0;
const TIMESTEP: f64 = 5.0 / 60.0;
struct Map {
    rooms: HashMap<String, Room>,
    move_index: usize,
    start: String,
    end: String,
    moves: Vec<Vec<String>>,
    borders: Borders,
    paths: Vec<String>,
}
#[derive(Debug)]
struct Borders {
    left: i32,
    right: i32,
    top: i32,
    bottom: i32,
}

#[derive(Debug, Default)]
struct Room {
    coordinates: (i32, i32),
    links: Vec<String>,
}

#[derive(Component)]
struct Edge;

#[derive(Component)]
struct RoomComponent;

fn main() {
    App::new()
        .insert_resource(WindowDescriptor {
            title: "Lem-in Visualizer".to_string(),
            width: WIDTH,
            height: HEIGHT,
            ..Default::default()
        })
        .insert_resource(ClearColor(Color::BLACK))
        .insert_resource(Map {
            rooms: HashMap::new(),
            move_index: 0,
            start: String::new(),
            end: String::new(),
            moves: Vec::new(),
            borders: Borders {
                left: i32::MAX,
                right: i32::MIN,
                top: i32::MIN,
                bottom: i32::MAX,
            },
            paths: Vec::new(),
        })
        .add_plugins(DefaultPlugins)
        .add_system(bevy::input::system::exit_on_esc_system)
        .add_startup_system(spawn_camera.label("camera"))
        .add_startup_system(parse.label("parse"))
        .add_startup_system(render.after("camera").after("parse"))
		.add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIMESTEP))
                .with_system(animate),
        )
        .run()
}

fn parse(mut data: ResMut<Map>) {
    let args: Vec<String> = env::args().collect();
    let file = &args[1];
    let input = read_to_string(file).unwrap();
    let parts: Vec<&str> = input.split("\n\n").collect();
    let map = parts[0];
    data.paths = parts[1].lines().map(|l| l.to_string()).collect();
    let moves = parts[2];
    let map_iter = map.lines().collect::<Vec<&str>>();
    let moves = moves.lines().filter(|a| a.len() > 0).collect::<Vec<&str>>();
    let map_iter = map_iter[1..].iter().enumerate();
    for (i, line) in map_iter {
        let re = Regex::new(r".+ .+ .+").unwrap();
        let caps = re.captures(line);
        if line.chars().collect::<Vec<char>>()[0] == '#' {
            continue;
        } else if caps.is_some() {
            let tmp_room: Vec<&str> = line.split(" ").collect();
            if map.lines().collect::<Vec<&str>>()[i].contains("start") {
                data.start = tmp_room[0].to_string();
            } else if map.lines().collect::<Vec<&str>>()[i].contains("end") {
                data.end = tmp_room[0].to_string();
            }
            let x = tmp_room[1].parse().unwrap();
            let y = tmp_room[2].parse().unwrap();
            data.borders.left = min(data.borders.left, x);
            data.borders.right = max(data.borders.right, x);
            data.borders.bottom = min(data.borders.bottom, y);
            data.borders.top = max(data.borders.top, y);
            data.rooms.insert(
                tmp_room[0].to_string(),
                Room {
                    coordinates: (x, y),
                    links: Vec::new(),
                },
            );
        } else {
            let tmp_link: Vec<&str> = line.split("-").collect();
            let tmp = data.rooms.entry(tmp_link[0].to_string()).or_default();
            tmp.links.push(tmp_link[1].to_string());
            let tmp = data.rooms.entry(tmp_link[1].to_string()).or_default();
            tmp.links.push(tmp_link[0].to_string());
        }
    }
    for (i, line) in moves.iter().enumerate() {
        let ant_moves: Vec<&str> = line.split(" ").collect();
        data.moves.push(Vec::new());
        for ant_move in ant_moves {
            let (_ant, room) = ant_move.split_once("-").unwrap();
            data.moves[i].push(room.to_string());
        }
    }
    println!("{} {}", data.start, data.end);
}

fn render(mut commands: Commands, map: Res<Map>) {
    let x_offset: f32 = (WIDTH - OFFSET * 2.0) / (map.borders.right - map.borders.left) as f32;
    let y_offset: f32 = (HEIGHT - OFFSET * 2.0) / (map.borders.top - map.borders.bottom) as f32;
    let mut edges: HashMap<String, Vec<String>> = HashMap::new();
    for (i, room) in &map.rooms {
        edges.insert(i.to_string(), Vec::new());
        for neighbour in &room.links {
            if !edges.contains_key(neighbour) || !edges.get(neighbour).unwrap().contains(i) {
                edges.get_mut(i).unwrap().push(neighbour.to_string());
            }
        }
    }

    for (room, neighbours) in &edges {
        for neighbour in neighbours {
            let first = map.rooms.get(room).unwrap();
            let second = map.rooms.get(neighbour).unwrap();
            let x_dif = (first.coordinates.0 - second.coordinates.0) as f64;
            let y_dif = (first.coordinates.1 - second.coordinates.1) as f64;
            let angle = atan2(y_offset as f64 * y_dif, x_offset as f64 * x_dif);
            commands
                .spawn_bundle(SpriteBundle {
                    sprite: Sprite {
                        color: Color::DARK_GRAY,
                        custom_size: Some(Vec2::new(
                            hypot(x_dif.abs() * x_offset as f64, y_dif.abs() * y_offset as f64)
                                as f32,
                            1.0,
                        )),
                        ..default()
                    },
                    transform: Transform {
                        translation: Vec3::new(
                            OFFSET
                                + x_offset
                                    * (min(first.coordinates.0, second.coordinates.0) as f32
                                        + x_dif.abs() as f32 / 2.0
                                        - map.borders.left as f32)
                                        as f32
                                - WIDTH / 2.0,
                            OFFSET
                                + y_offset
                                    * (min(first.coordinates.1, second.coordinates.1) as f32
                                        + y_dif.abs() as f32 / 2.0
                                        - map.borders.bottom as f32)
                                        as f32
                                - HEIGHT / 2.0,
                            0.0,
                        ),
                        rotation: Quat::from_rotation_z(angle as f32),
                        ..Default::default()
                    },
                    ..default()
                })
                .insert(Edge);
        }
    }

    for (i, room) in &map.rooms {
        let size = if *i == map.start || *i == map.end {
            10.0
        } else {
            3.0
        };
        let color = if *i == map.start || *i == map.end {
            Color::WHITE
        } else {
            Color::DARK_GRAY
        };
        commands.spawn_bundle(SpriteBundle {
            sprite: Sprite {
                color,
                custom_size: Some(Vec2::new(size, size)),
                ..default()
            },
            transform: Transform {
                translation: Vec3::new(
                    OFFSET + x_offset * (room.coordinates.0 - map.borders.left) as f32
                        - WIDTH / 2.0,
                    OFFSET + y_offset * (room.coordinates.1 - map.borders.bottom) as f32
                        - HEIGHT / 2.0,
                    if *i == map.start || *i == map.end {
                        1.0
                    } else {
                        0.0
                    },
                ),
                ..Default::default()
            },
            ..default()
        });
    }

    let colors = vec![
        Color::YELLOW,
        Color::TOMATO,
        Color::BLUE,
        Color::GREEN,
        Color::MAROON,
        Color::PINK,
        Color::PURPLE,
        Color::DARK_GREEN,
        Color::AQUAMARINE,
        Color::RED,
        Color::OLIVE,
    ];
    for (i, line) in map.paths[1..].iter().enumerate() {
        let path = line.split_once(": ").unwrap();
        let path = path.1;
        let path: Vec<String> = path.split(" ").map(|l| l.to_string()).collect();
        for (index, room) in path[1..].iter().enumerate() {
            if index == path.len() - 2 {
                continue;
            }
            let first = map.rooms.get(room).unwrap();
            let second = map.rooms.get(&path[index]).unwrap();
            let x_dif = (first.coordinates.0 - second.coordinates.0) as f64;
            let y_dif = (first.coordinates.1 - second.coordinates.1) as f64;
            let angle = atan2(y_offset as f64 * y_dif, x_offset as f64 * x_dif);
            commands
                .spawn_bundle(SpriteBundle {
                    sprite: Sprite {
                        color: colors[i % colors.len()],
                        custom_size: Some(Vec2::new(
                            hypot(x_dif.abs() * x_offset as f64, y_dif.abs() * y_offset as f64)
                                as f32,
                            1.0,
                        )),
                        ..default()
                    },
                    transform: Transform {
                        translation: Vec3::new(
                            OFFSET
                                + x_offset
                                    * (min(first.coordinates.0, second.coordinates.0) as f32
                                        + x_dif.abs() as f32 / 2.0
                                        - map.borders.left as f32)
                                        as f32
                                - WIDTH / 2.0,
                            OFFSET
                                + y_offset
                                    * (min(first.coordinates.1, second.coordinates.1) as f32
                                        + y_dif.abs() as f32 / 2.0
                                        - map.borders.bottom as f32)
                                        as f32
                                - HEIGHT / 2.0,
                            0.0,
                        ),
                        rotation: Quat::from_rotation_z(angle as f32),
                        ..Default::default()
                    },
                    ..default()
                })
                .insert(Edge);
            commands.spawn_bundle(SpriteBundle {
                sprite: Sprite {
                    color: colors[i % colors.len()],
                    custom_size: Some(Vec2::new(5.0, 5.0)),
                    ..default()
                },
                transform: Transform {
                    translation: Vec3::new(
                        OFFSET + x_offset * (first.coordinates.0 - map.borders.left) as f32
                            - WIDTH / 2.0,
                        OFFSET + y_offset * (first.coordinates.1 - map.borders.bottom) as f32
                            - HEIGHT / 2.0,
                        0.0,
                    ),
                    ..Default::default()
                },
                ..default()
            });
        }
    }
}

fn animate(
    mut commands: Commands,
    mut map: ResMut<Map>,
    last_moves: Query<Entity, With<RoomComponent>>,
) {
    let x_offset: f32 = (WIDTH - OFFSET * 2.0) / (map.borders.right - map.borders.left) as f32;
    let y_offset: f32 = (HEIGHT - OFFSET * 2.0) / (map.borders.top - map.borders.bottom) as f32;
    for room in last_moves.iter() {
        commands.entity(room).despawn();
    }
    for room in &map.moves[map.move_index] {
        commands
            .spawn_bundle(SpriteBundle {
                sprite: Sprite {
                    color: Color::WHITE,
                    custom_size: Some(Vec2::new(5.0, 5.0)),
                    ..default()
                },
                transform: Transform {
                    translation: Vec3::new(
                        OFFSET
                            + x_offset
                                * (map.rooms.get(room).unwrap().coordinates.0 - map.borders.left)
                                    as f32
                            - WIDTH / 2.0,
                        OFFSET
                            + y_offset
                                * (map.rooms.get(room).unwrap().coordinates.1 - map.borders.bottom)
                                    as f32
                            - HEIGHT / 2.0,
                        0.0,
                    ),
                    ..Default::default()
                },
                ..default()
            })
            .insert(RoomComponent);
    }
    map.move_index += 1;
    if map.move_index == map.moves.len() {
        map.move_index = 0;
    }
}
fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
}
