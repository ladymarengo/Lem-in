use std::{env, fs::read_to_string, collections::HashMap};

use bevy::prelude::*;
const WIDTH: f32 = 900.0;
const HEIGHT: f32 = 600.0;
struct Map {
	rooms: HashMap<String, Room>,
}

#[derive(Debug, Default)]
struct Room {
	coordinates: (i32, i32),
	room_type: RoomType,
	links: Vec<String>,
}
#[derive(Debug, Default)]
enum RoomType {
	#[default] Start,
	Middle,
	End,
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
	let mut data: Map = Map{rooms: HashMap::new()};
	let map_iter = map.lines().collect::<Vec<&str>>();
	let map_iter = map_iter[1..].iter().enumerate();
	for (i, line) in map_iter{
		if (line.chars().collect::<Vec<char>>()[0] == '#')
		{
			continue ;
		}
		else if line.contains("-")
		{
			let tmp_link: Vec<&str> = line.split("-").collect();
			//data.rooms[tmp_link[0]].links.push(tmp_link[1].to_string());
			let tmp = data.rooms.entry(tmp_link[0].to_string()).or_default();
			tmp.links.push(tmp_link[1].to_string());
			let tmp = data.rooms.entry(tmp_link[1].to_string()).or_default();
			tmp.links.push(tmp_link[0].to_string());
		}
		else
		{
			let tmp_room: Vec<&str> = line.split(" ").collect();
			let room_type = if map.lines().collect::<Vec<&str>>()[i].contains("start") {RoomType::Start} else if map.lines().collect::<Vec<&str>>()[i].contains("end") {RoomType::End} else {RoomType::Middle};
			data.rooms.insert(tmp_room[0].to_string(), Room{coordinates: (tmp_room[1].parse().unwrap(), tmp_room[2].parse().unwrap()), room_type, links: Vec::new()});
		}
	}
	println!("{:?}", data.rooms);
}

fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
}
