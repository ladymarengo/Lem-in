use std::{
    cmp::{max, min},
    collections::HashMap,
    env,
    fs::read_to_string, f64::consts::PI,
};

use libm::{atan2, hypot};
use regex::Regex;
use bevy::{prelude::*, sprite::MaterialMesh2dBundle};
use fdg_sim::{ForceGraph, ForceGraphHelper, Simulation, SimulationParameters, petgraph::graph::NodeIndex};
const WIDTH: f32 = 1800.0;
const HEIGHT: f32 = 1200.0;
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
    node_index: Option<NodeIndex>,
}
#[derive(Debug, Default, PartialEq)]
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
		let re = Regex::new(r".+ .+ .+").unwrap();
		let caps = re.captures(line);
        if line.chars().collect::<Vec<char>>()[0] == '#' {
            continue;
        }  
		else if caps.is_some(){
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
                    node_index: None,
                },
            );
        }
		else {
            let tmp_link: Vec<&str> = line.split("-").collect();
            //data.rooms[tmp_link[0]].links.push(tmp_link[1].to_string());
            let tmp = data.rooms.entry(tmp_link[0].to_string()).or_default();
            tmp.links.push(tmp_link[1].to_string());
            let tmp = data.rooms.entry(tmp_link[1].to_string()).or_default();
            tmp.links.push(tmp_link[0].to_string());
        }
    }
    for (i, line) in moves.iter().enumerate() {
        let ant_moves: Vec<&str> = line.split(" ").collect();
        for ant_move in ant_moves {
            let (ant, room) = ant_move.split_once("-").unwrap();
            data.rooms.get_mut(room).unwrap().on_path = true;
            data.ants[ant[1..].parse::<usize>().unwrap() - 1].position[i] = room.to_string();
        }
    }
    println!("{:?}", data.borders);
    // for room in &data.rooms {
    //     println!("{} {} {}", room.0, room.1.coordinates.0, room.1.coordinates.1);
    // }

    // let mut graph: ForceGraph<(), ()> = ForceGraph::default();

    // for room in &mut data.rooms {
    //     room.1.node_index = Some(graph.add_force_node(room.0, ()));
    // }

    // for room in &data.rooms {
    //     for neighbour in &room.1.links {
            
    //         graph.add_edge(room.1.node_index.unwrap(), data.rooms[neighbour].node_index.unwrap(), ());
    //     }
    // }

    // // create a simulation from the graph
    // let mut simulation = Simulation::from_graph(&graph, SimulationParameters::default());

    // // your event/render loop
    // for frame in 0..100 {
    //     // update the nodes positions based on force algorithm
    //     simulation.update(0.035);
    // }

    // println!("After simulation:");
    // for node in simulation.get_graph().node_weights() {
    //     data.rooms.get_mut(&node.name).unwrap().coordinates = (node.location.x as i32, node.location.y as i32);
    //     let x = node.location.x as i32;
    //     let y = node.location.y as i32;
    //     data.borders.left = min(data.borders.left, x);
    //     data.borders.right = max(data.borders.right, x);
    //     data.borders.bottom = min(data.borders.bottom, y);
    //     data.borders.top = max(data.borders.top, y);
    //     // println!("\"{}\" - {:?}", node.name, node.location);
    // }
    // for room in &data.rooms {
    //     println!("{} {} {}", room.0, room.1.coordinates.0, room.1.coordinates.1);
    // }

}

fn render(
    mut commands: Commands,
    map: Res<Map>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<ColorMaterial>>,
) {
    let x_offset: f32 = (WIDTH - OFFSET * 2.0) / (map.borders.right - map.borders.left) as f32;
    let y_offset: f32 = (HEIGHT - OFFSET * 2.0) / (map.borders.top - map.borders.bottom) as f32;
	// let offset = (HEIGHT - OFFSET * 2.0) / max(map.borders.right - map.borders.left,)
	let mut edges: HashMap<String, Vec<String>> = HashMap::new();
    for (i, room) in &map.rooms {
		edges.insert(i.to_string(), Vec::new());
        for neighbour in &room.links {
			if !edges.contains_key(neighbour) || !edges.get(neighbour).unwrap().contains(i){
				edges.get_mut(i).unwrap().push(neighbour.to_string());
				}
			}
		let size = if room.room_type == RoomType::Start || room.room_type == RoomType::End {5.0} else if room.on_path {3.0} else {3.0};
        commands.spawn_bundle(SpriteBundle {
            sprite: Sprite {
                color: if room.room_type == RoomType::Start {Color::GREEN} else if room.room_type == RoomType::End {Color::BLACK} else if room.on_path {Color::RED} else {Color::BLUE},
                custom_size: Some(Vec2::new(size, size)),
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
        }).insert(RoomComponent);
    }

	for (room, neighbours) in &edges{
		for neighbour in neighbours{
			let first = map.rooms.get(room).unwrap();
			let second = map.rooms.get(neighbour).unwrap();
			let x_dif = (first.coordinates.0 - second.coordinates.0) as f64;
			let y_dif = (first.coordinates.1 - second.coordinates.1) as f64;
			let angle = atan2(y_offset as f64 * y_dif, x_offset as f64 * x_dif);
			commands.spawn_bundle(SpriteBundle {
				sprite: Sprite {
					color: if  first.on_path &&  second.on_path {Color::RED} else {Color::BLUE},
					custom_size: Some(Vec2::new(hypot(x_dif.abs() * x_offset as f64, y_dif.abs() * y_offset as f64) as f32, 1.0)),
					..default()
				},
				transform: Transform {
					translation: Vec3::new(
						OFFSET + x_offset * (min(first.coordinates.0, second.coordinates.0) as f32 + x_dif.abs() as f32 / 2.0 - map.borders.left as f32) as f32 - WIDTH / 2.0,
						OFFSET + y_offset * (min(first.coordinates.1, second.coordinates.1) as f32 + y_dif.abs() as f32 / 2.0 - map.borders.bottom as f32) as f32 - HEIGHT / 2.0,
						0.0
					),
					rotation: Quat::from_rotation_z(angle as f32), 
					..Default::default()
				},
				..default()
			}).insert(Edge);
		}
	} 
}

fn rotate(mut rooms: Query<&mut Transform, With<RoomComponent>>){
	// for mut room in rooms.iter_mut(){
	// 	room.rotate_around(point, rotation)
	// }

}

fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
}
