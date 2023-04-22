struct Solution;

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut result = vec![];
        for (i, x) in nums.iter().enumerate() {
            for (j, y) in nums.iter().enumerate() {
                if i == j {
                    continue;
                }
                if x + y == target {
                    result.push(i as i32);
                    result.push(j as i32);
                    return result;
                }
            }
        }
        result
    }
}

fn main() {
    let nums = vec![1, 2, 3, 4, 5];
    let r = Solution::two_sum(nums, 6);
    println!("{:?}", r);
}
