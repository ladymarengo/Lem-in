use std::{
    cmp::{max, min},
    collections::HashMap,
    env,
    fs::read_to_string,
};

use bevy::{prelude::*, sprite::MaterialMesh2dBundle};
use bevy_prototype_lyon::prelude::*;
const WIDTH: f32 = 900.0;
const HEIGHT: f32 = 600.0;
const OFFSET: f32 = 20.0;
struct Map {
    rooms: HashMap<String, Room>,
    ants: Vec<Ant>,
    borders: Borders,
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
    room_type: RoomType,
    links: Vec<String>,
    on_path: bool,
}
#[derive(Debug, Default)]
enum RoomType {
    #[default]
    Start,
    Middle,
    End,
}

#[derive(Clone, Debug)]
struct Ant {
    position: Vec<String>,
}

fn main() {
    App::new()
        .insert_resource(WindowDescriptor {
            title: "Lem-in Visualizer".to_string(),
            width: WIDTH,
            height: HEIGHT,
            ..Default::default()
        })
        .insert_resource(ClearColor(Color::hsl(26.0, 0.32, 0.73)))
        .insert_resource(Map {
            rooms: HashMap::new(),
            ants: Vec::new(),
            borders: Borders {
                left: i32::MAX,
                right: i32::MIN,
                top: i32::MIN,
                bottom: i32::MAX,
            },
        })
        .add_plugins(DefaultPlugins)
        .add_system(bevy::input::system::exit_on_esc_system)
        .add_startup_system(spawn_camera.label("camera"))
        .add_startup_system(parse.label("parse"))
        .add_startup_system(render.after("camera").after("parse"))
        .run()
}

fn parse(mut commands: Commands, mut data: ResMut<Map>) {
    let args: Vec<String> = env::args().collect();
    let file = &args[1];
    let input = read_to_string(file).unwrap();
    let (map, moves) = input.split_once("\n\n").unwrap();
    let map_iter = map.lines().collect::<Vec<&str>>();
    let moves = moves.lines().filter(|a| a.len() > 0).collect::<Vec<&str>>();
    data.ants = vec![
        Ant {
            position: vec![String::new(); moves.len()]
        };
        map_iter[0].parse().unwrap()
    ];
    let map_iter = map_iter[1..].iter().enumerate();
    for (i, line) in map_iter {
        if line.chars().collect::<Vec<char>>()[0] == '#' {
            continue;
        } else if line.contains("-") {
            let tmp_link: Vec<&str> = line.split("-").collect();
            //data.rooms[tmp_link[0]].links.push(tmp_link[1].to_string());
            let tmp = data.rooms.entry(tmp_link[0].to_string()).or_default();
            tmp.links.push(tmp_link[1].to_string());
            let tmp = data.rooms.entry(tmp_link[1].to_string()).or_default();
            tmp.links.push(tmp_link[0].to_string());
        } else {
            let tmp_room: Vec<&str> = line.split(" ").collect();
            let room_type = if map.lines().collect::<Vec<&str>>()[i].contains("start") {
                RoomType::Start
            } else if map.lines().collect::<Vec<&str>>()[i].contains("end") {
                RoomType::End
            } else {
                RoomType::Middle
            };
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
                    room_type,
                    links: Vec::new(),
                    on_path: false,
                },
            );
        }
    }
    for (i, line) in moves.iter().enumerate() {
        let ant_moves: Vec<&str> = line.split(" ").collect();
        for ant_move in ant_moves {
            let (ant, room) = ant_move.split_once("-").unwrap();
            data.ants[ant[1..].parse::<usize>().unwrap() - 1].position[i] = room.to_string();
        }
    }
    println!("{:?}", data.borders);
}

fn render(
    mut commands: Commands,
    map: Res<Map>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<ColorMaterial>>,
) {
    let x_offset: f32 = (WIDTH - OFFSET * 2.0) / (map.borders.right - map.borders.left) as f32;
    let y_offset: f32 = (HEIGHT - OFFSET * 2.0) / (map.borders.top - map.borders.bottom) as f32;

    for room in map.rooms.values() {
        commands.spawn_bundle(SpriteBundle {
            sprite: Sprite {
                color: Color::rgb(0.25, 0.25, 0.75),
                custom_size: Some(Vec2::new(5.0, 5.0)),
                ..default()
            },
			transform: Transform {
				translation: Vec3::new(
					OFFSET + x_offset * (room.coordinates.0 - map.borders.left) as f32 - WIDTH / 2.0,
					OFFSET + y_offset * (room.coordinates.1 - map.borders.bottom) as f32 - HEIGHT / 2.0,
					0.0
				),
				..Default::default()
			},
            ..default()
        });
    }
}

fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
}
