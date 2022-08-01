use std::{collections::HashMap, env, fs::read_to_string};

use bevy::prelude::*;
const WIDTH: f32 = 900.0;
const HEIGHT: f32 = 600.0;
struct Map {
    rooms: HashMap<String, Room>,
    ants: Vec<Ant>,
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
        .add_plugins(DefaultPlugins)
        .add_system(bevy::input::system::exit_on_esc_system)
        .add_startup_system(spawn_camera)
        .add_startup_system(parse)
        .run()
}

fn parse(mut commands: Commands) {
    let args: Vec<String> = env::args().collect();
    let file = &args[1];
    let input = read_to_string(file).unwrap();
    let (map, moves) = input.split_once("\n\n").unwrap();
    let map_iter = map.lines().collect::<Vec<&str>>();
    let mut data: Map = Map {
        rooms: HashMap::new(),
        ants: vec![
            Ant {
                position: vec![
                    String::new();
                    moves
                        .lines()
                        .filter(|a| a.len() > 0)
                        .collect::<Vec<&str>>()
                        .len()
                ]
            };
            map_iter[0].parse().unwrap()
        ],
    };
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
            data.rooms.insert(
                tmp_room[0].to_string(),
                Room {
                    coordinates: (tmp_room[1].parse().unwrap(), tmp_room[2].parse().unwrap()),
                    room_type,
                    links: Vec::new(),
                    on_path: false,
                },
            );
        }
    }
    // for line in moves.lines() {
    // 	let ant_moves: Vec<&str> = line.split(" ").collect();
    // 	for (i, ant_move) in ant_moves.iter().enumerate(){
    // 		let (ant, room) = ant_move.split_once("-").unwrap();
    // 		data.ants[ant[1..].parse::<usize>().unwrap()].position[i]

    // 	}

    // }
    println!("{:?}", data.ants);
}

fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
}
