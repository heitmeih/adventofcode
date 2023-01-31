use std::fs;

fn main() {

    let raw_data = fs::read_to_string("./day1.in").expect("could not read input");

    // needlessly short version
    // let mut thing: Vec<u32> = raw_data.split("\r\n\r\n").map(|section| section.lines().map(|cal| cal.parse::<u32>().unwrap()).sum::<u32>()).collect();
    // thing.sort_by(|a, b| b.cmp(a));

    // println!("Part 1: {}\nPart 2: {}", thing[0], thing[0..3].iter().sum::<u32>());

    let mut elves: Vec<u32> = Vec::new();
    let mut calories = 0u32;

    for line in raw_data.lines() {
        if line == "" {
            elves.push(calories);
            calories = 0;
        } else {
            calories += line.parse::<u32>().unwrap();
        }
    }

    elves.sort_by(|a, b| b.cmp(a));

    println!("Part 1: {}", elves[0]);
    println!("Part 2: {}", elves[0..3].iter().sum::<u32>())
}