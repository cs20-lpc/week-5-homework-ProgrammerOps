#include <iostream>

struct Node {
    int val;
    Node* next;
    Node(int v=0) : val(v), next(nullptr) {}
};

// Floyd's cycle-finding algorithm (Tortoise and Hare)

bool hasCycle(Node* head) {               //Function that answers: “Does our train loop in a circle?” Input: head is the first wagon’s address. Output: true if there’s a loop, false if not.
    // TO DO: Implement your code here. 
 


//Commment: we're going to impllement the classic tortoise & hare trick to detect loops.

// If list is empty or has a single node, it cannot form a cycle
    

     if (head == nullptr || head->next == nullptr) {     //No wagons or only one wagon? There’s no way to loop.
        return false;
    }

    Node* slow = head;        // Tortosie moves 1 step on first wagon)
    Node* fast = head->next;  // Hare starts ahead and moves 2 steps starts one ahead)

    // Move until fast falls off (no cycle) or slow catches fast (cycle)
    while (fast != nullptr && fast->next != nullptr) {   //The hare needs two steps; if there isn’t a next or a next-next, we’ve reached the end → no loop.
        if (slow == fast) {    //If they point to the same exact wagon, the hare has lapped the tortoise → the track loops.
            return true; // pointers met → loop exists
        }
        slow = slow->next;           // 1 step       
        fast = fast->next->next;     // 2 steps
    }

    // fast hit the end → no cycle    //We return false; the hare fell off the track (hit nullptr), so it’s a straight list.
    return false;








}

// Helper to create a singly linked list with n nodes. Returns head and optionally
// a pointer to the node at index "linkIndex" (0-based) so we can form a cycle.
// If linkIndex < 0, that pointer will be nullptr.
Node* createList(int n, Node** outLinkNode = nullptr, int linkIndex = -1) {
    if (n <= 0) {
        if (outLinkNode) *outLinkNode = nullptr;
        return nullptr;
    }
    Node* head = new Node(1);
    Node* tail = head;
    Node* linkNode = nullptr;
    if (linkIndex == 0) linkNode = head;

    for (int i = 2; i <= n; ++i) {
        tail->next = new Node(i);
        tail = tail->next;
        if (i - 1 == linkIndex) linkNode = tail; // linkIndex is 0-based
    }

    if (outLinkNode) *outLinkNode = linkNode;
    return head;
}

// Delete a (now acyclic) linked list safely.
void deleteList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    const int N = 1000;

    // --- Test 1: List with NO cycle ---
    Node* head1 = createList(N);
      std::cout <<  (hasCycle(head1) ? "true " : "false ");
    // clean up
    deleteList(head1);

    // --- Test 2: List WITH a cycle ---
    // Re-create the list and make the last node point to node at index 500 (0-based)
    Node* linkNode = nullptr;
    Node* head2 = createList(N, &linkNode, 500); // linkNode points to node #501
    // find tail
    Node* tail = head2;
    while (tail && tail->next) tail = tail->next;
    if (tail) {
        tail->next = linkNode; // create cycle
     } else {
        std::cout << "Test 2 - Unexpected: tail is null.\n";
    }

    std::cout << (hasCycle(head2) ? "true" : "false") << "\n";

    // Break the cycle (so we can delete safely)
    if (tail) tail->next = nullptr;
    deleteList(head2);

    return 0;
}