use std::fs;

fn calculate_score(opponent_selection: i32, player_selection: i32) -> i32 {
    // 1 beats 3
    // 2 beats 1
    // 3 beats 2

    let diff = (player_selection - opponent_selection).abs() - 1;
    let op_val = (opponent_selection + diff) % 4;
    let player_val = (player_selection +  diff) % 4;

    if op_val < player_val {
        6
    } else if op_val == player_val {
        3
    } else {
        0
    }
}

fn get_loser_to(winning_val: i32) -> i32 {
    // 1 beats 3
    // 2 beats 1
    // 3 beats 2

    // 1 -> ((1-1 + 2) % 3) + 1 = (2 % 3) + 1 = 2 + 1 = 3
    // 2 -> ((2-1 + 2) % 3) + 1 = (3 % 3) + 1 = 0 + 1 = 1
    // 3 -> ((3-1 + 2) % 3) + 1 = (4 % 3) + 1 = 1 + 1 = 2
    ((winning_val-1 + 2) % 3) + 1
}

fn get_winner_to(losing_val: i32) -> i32 {
    // 1 beats 3
    // 2 beats 1
    // 3 beats 2

    // 1 -> ((1-1 + 4) % 3) + 1 = (4 % 3) + 1 = 1 + 1 = 2
    // 2 -> ((2-1 + 4) % 3) + 1 = (5 % 3) + 1 = 2 + 1 = 3
    // 3 -> ((3-1 + 4) % 3) + 1 = (6 % 3) + 1 = 0 + 1 = 1
    ((losing_val-1 + 4) % 3) + 1
}

fn main() {
    let raw_data = fs::read_to_string("./day2.in").expect("could not read input");

    let data: Vec<(i32, i32)> = raw_data.lines().map(|line| line.split(" ").map(|c| match c {
        "A" | "X" => 1,
        "B" | "Y" => 2,
        "C" | "Z" => 3,
        _ => -10
    }).collect()).map(|pair: Vec<i32>| (pair[0], pair[1])).collect();

    let mut p1_total_score = 0;
    let mut p2_total_score = 0;
    for (opponent, player) in data {
        p1_total_score += player + calculate_score(opponent, player);

        if player == 1 { // lose
            p2_total_score += get_loser_to(opponent);
        } else if player == 2 { // tie
            p2_total_score += 3 + opponent;
        } else { // win
            p2_total_score += 6 + get_winner_to(opponent);
        }
    }

    println!("Part 1: {}\nPart 2: {}", p1_total_score, p2_total_score);
}