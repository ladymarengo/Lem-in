use fdg_sim::{
    petgraph::graph::NodeIndex, ForceGraph, ForceGraphHelper, Simulation, SimulationParameters,
};
use std::io::Write;
use std::process::exit;
use std::{
    collections::HashMap,
    env,
    fs::{read_to_string, File},
};

#[derive(Debug, Default)]
struct Room {
    coordinates: (i32, i32),
    links: Vec<String>,
    node_index: Option<NodeIndex>,
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() == 1 {
        print_usage();
    }

    let file = &args[1];
    let mut iterations = 150;
    if args.len() > 2 {
        let tmp = args[2].parse::<i32>();
        match tmp {
            Ok(v) => iterations = v,
            Err(_e) => print_usage(),
        }
    }

    let tmp = read_to_string(file);
    let mut map = String::new();
    match tmp {
        Ok(v) => map = v,
        Err(_e) => print_usage(),
    }
    let map_iter = map.lines().collect::<Vec<&str>>();
    let mut rooms: HashMap<String, Room> = HashMap::new();

    for line in &map_iter[1..] {
        if line.chars().collect::<Vec<char>>()[0] == '#' {
            continue;
        } else if line.contains("-") {
            let tmp_link: Vec<&str> = line.split("-").collect();
            let tmp = rooms.entry(tmp_link[0].to_string()).or_default();
            tmp.links.push(tmp_link[1].to_string());
            let tmp = rooms.entry(tmp_link[1].to_string()).or_default();
            tmp.links.push(tmp_link[0].to_string());
        } else {
            let tmp_room: Vec<&str> = line.split(" ").collect();
            let x = tmp_room[1].parse().unwrap();
            let y = tmp_room[2].parse().unwrap();
            rooms.insert(
                tmp_room[0].to_string(),
                Room {
                    coordinates: (x, y),
                    links: Vec::new(),
                    node_index: None,
                },
            );
        }
    }

    let mut graph: ForceGraph<(), ()> = ForceGraph::default();
    for room in &mut rooms {
        room.1.node_index = Some(graph.add_force_node(room.0, ()));
    }

    let mut edges: HashMap<String, Vec<String>> = HashMap::new();
    for room in &rooms {
        edges.insert(room.0.to_string(), Vec::new());
        for neighbour in &room.1.links {
            if !edges.contains_key(neighbour) || !edges.get(neighbour).unwrap().contains(room.0) {
                graph.add_edge(
                    room.1.node_index.unwrap(),
                    rooms[neighbour].node_index.unwrap(),
                    (),
                );
            }
            edges.get_mut(room.0).unwrap().push(neighbour.to_string());
        }
    }

    // create a simulation from the graph
    let mut simulation = Simulation::from_graph(&graph, SimulationParameters::default());

    // Untangling the graph (more iterations equals more untangling)
    for _frame in 0..iterations {
        simulation.update(0.035);
    }

    for node in simulation.get_graph().node_weights() {
        rooms.get_mut(&node.name).unwrap().coordinates =
            (node.location.x as i32, node.location.y as i32);
    }

    let mut output = File::create(format!("{}-beautified-{}", file, iterations)).unwrap();
    for (i, line) in map.lines().enumerate() {
        if !line.contains("-") && !line.contains("#") && i != 0 {
            let tmp_room: Vec<&str> = line.split(" ").collect();
            writeln!(
                output,
                "{} {} {}",
                tmp_room[0], rooms[tmp_room[0]].coordinates.0, rooms[tmp_room[0]].coordinates.1
            );
        } else {
            writeln!(output, "{line}");
        }
    }
    write!(output, "#Beautified");
    println!("Beautified with {} iterations!", iterations);
}

fn print_usage() {
    println!("Usage:\nFirst argument is the name of the map\nSecond argument (optional) is number of iterations, default is 150.");
    exit(0);
}
