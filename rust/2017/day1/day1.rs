use std::fs;

fn main() {
    let raw = fs::read_to_string("./day1.in")
        .expect("Could not read file!");
    let data: Vec<u16> = raw.chars().map(|c| c.to_digit(10).unwrap() as u16).collect();

    let (mut sum_p1, mut sum_p2): (u16, u16) = (0, 0);

    for i in 0..data.len() {
        let (curr, next_p1, next_p2) = (data[i], data[(i + 1) % data.len()], data[(i + data.len() / 2) % data.len()]);
        
        if curr == next_p1 {
            sum_p1 += curr;
        }

        if curr == next_p2 {
            sum_p2 += curr;
        }

    }

    println!("Part 1: {}\nPart 2: {}", sum_p1, sum_p2);
}