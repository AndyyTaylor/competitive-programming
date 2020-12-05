/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) {
            return NULL;
        }

        unordered_map<Node*, Node*> nodeMap;

        Node* newHead = new Node(head->val);
        newHead->random = head->random;
        Node* prevNode = newHead;
        nodeMap[head] = newHead;

        Node* cur = head->next;
        while (cur != NULL) {
            Node* n = new Node(cur->val);
            n->random = cur->random;
            prevNode->next = n;
            nodeMap[cur] = n;

            prevNode = n;
            cur = cur->next;
        }

        cur = newHead;
        while (cur != NULL) {
            if (cur->random != NULL) {
                cur->random = nodeMap[cur->random];
            }

            cur = cur->next;
        }

        return newHead;
    }
};
