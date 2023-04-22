pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

type Link = Option<Box<ListNode>>;

fn push(head: &mut Link, val: i32) -> &mut Link {
    let new_node = Box::new(ListNode {
        val: val,
        next: None,
    });
    match head {
        None => &mut Some(new_node),
        Some(node) => {
            node.next = Some(new_node);
            &mut node.next
        }
    }
}

fn out(head: &Link) {}

struct Solution;

impl Solution {
    pub fn merge_two_lists(
        list1: Option<Box<ListNode>>,
        list2: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        let res = None;
        res
    }
}

fn main() {
    let mut head = None;
    push(&mut head, 1);
    push(&mut head, 2);
    out(&head);
}
