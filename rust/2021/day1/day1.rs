use std::fs;

fn main() {
    let raw = fs::read_to_string("./day1.in")
        .expect("Could not read file!");
    let lines: Vec<u16> = raw.lines().map(|x| x.parse::<u16>().unwrap()).collect();

    let mut part_1 = 0;
    let mut part_2 = 0;

    for i in 1..lines.len() {
        part_1 += (lines[i-1] < lines[i]) as u16;
    }

    for i in 3..lines.len() {
        part_2 += (lines[i-3] + lines[i-2] + lines[i-1] < lines[i-2] + lines[i-1] + lines[i]) as u16;
    }

    println!("Part 1: {}\nPart 2: {}", part_1, part_2);
}