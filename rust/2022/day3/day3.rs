use std::fs;

fn main() {
    let raw_data = fs::read_to_string("./day3.in").expect("could not read input");

    // part 1
    let mut p1_sum = 0u32;
    for line in raw_data.lines() {
        let first = &line[..line.len()/2];
        let second = &line[line.len()/2..line.len()];

        p1_sum += compare(first, second);
        
    }

    // part 2
    let mut p2_sum = 0u32;
    for lines in raw_data.lines().collect::<Vec<&str>>().chunks(3) {
        p2_sum += find_match(lines[0], lines[1], lines[2]);
    }


    println!("Part 1: {}\nPart 2: {}", p1_sum, p2_sum);
}

fn find_match(first: &str, second: &str, third: &str) -> u32 {
    for fc in first.chars() {
        for sc in second.chars() {
            for tc in third.chars() {
                if fc == sc && fc == tc {
                    return get_priority(fc);
                }
            }
        }
    }
    0
}

fn compare(first: &str, second: &str) -> u32 {
    for fc in first.chars() {
        for sc in second.chars() {
            if fc == sc {
                return get_priority(fc);
            }
        }
    }
    0
}

fn get_priority(c: char) -> u32 {
    if c < 'a' {
        c as u32 - 38
    } else {
        c as u32 - 96
    }
}