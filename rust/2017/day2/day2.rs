use std::fs;

// could return the division, but why not practice with tuples?
fn find_evenly_divisible(row: &Vec<u16>) -> (u16, u16) {
    for i in 0..(row.len() - 1) {
        for j in (i+1)..row.len() {
            if row[j] % row[i] == 0 {
                return (row[j], row[i]);
            } else if row[i] % row[j] == 0 {
                return (row[i], row[j]);
            }
        }
    }
    (0u16, 1u16) // in case it fails
}

fn main() {
    const FILENAME: &'static str = "./day2.in";
    let raw = fs::read_to_string(&FILENAME)
        .expect("Could not read file");
    let data: Vec<Vec<u16>> = raw.lines().map(|line| line.split_whitespace().map(|x| x.parse::<u16>().unwrap()).collect()).collect();

    let (mut part_1, mut part_2) = (0u16, 0u16);
    
    for row in data.iter() {
        part_1 += row.iter().max().unwrap() - row.iter().min().unwrap();
        let divisible = find_evenly_divisible(row);
        part_2 += divisible.0 / divisible.1;
    }

    println!("Part 1: {}\nPart 2: {}", part_1, part_2);
}