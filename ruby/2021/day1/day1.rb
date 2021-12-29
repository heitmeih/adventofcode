data = File.new("day1.in").read().split("\n").map { |num| num.to_i }

part_1, part_2 = 0, 0

data[0..-2].zip(data[1..]).each do |first, second|
    part_1 += 1 unless first >= second
end

puts part_1

data[0..-4].zip(data[1..-3], data[2..-2], data[3..]).each do |group|
    part_2 += 1 unless group[..-2].sum >= group[1..].sum    
end

puts part_2