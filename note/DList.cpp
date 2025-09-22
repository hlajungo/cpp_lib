#include "alluneed.h"
struct Node {
  Node(int v) : p(NUL), n(NUL), v(v) {}
  Node* p;
  Node* n;
  int v;
};
/*
 * @brief Doubly linked list
 */
struct DList {
  Node* head;
  Node* tail;
  size_t size;
  DList() : head(NUL), tail(NUL), size(0) {}
  DList(Node* head) : head(head), tail(head), size(1) {}
  /*
   * @brief Insert the ctx to the tail.
   * @param ctx the context for new node.
   */
  template<typename TCtx>
  void insert_tail(TCtx&& ctx) {
    // empty list
    if (head == NUL) {
      Node<Ctx>* n = new Node<Ctx>(std::forward<Ctx>(ctx));
      n->prev = NUL;
      n->next = NUL;
      head = n;
      tail = n;
      size++;
      return;
    }
    Node<Ctx>* n = new Node<Ctx>(std::forward<Ctx>(ctx));
    tail->next = n;
    n->prev = tail;
    n->next = NUL;
    tail = n;
    size++;
  }
  /*
   * @brief Remove ith node (0-index)
   */
  void remove(int i) {
    Node<Ctx>* t = head;
    while (t != NUL && t->val != i) { t = t->next; }
    if (t == NUL) { return; }
    if (t->prev == NUL) {
      if (t->next == NUL) {
        head = NUL;
      } else {
        head = t->next;
        head->prev = NUL;
      }
    } else if (t->next == NUL) {
      t->prev->next = NUL;
    } else {
      t->prev->next = t->next;
      t->next->prev = t->prev;
    }
    delete t;
  }
  /*
   * @brief Remove specfic Ctx by pointer
   */
  void remove(Node<Ctx>* t) {
    if (size == 0 || t == NUL) return;
    if (size == 1) {
      head = NUL;
      tail = NUL;
      delete t;
    } else if (t == head) {
      head = t->next;
      head->prev = NUL;
      delete t;
    } else if (t == tail) {
      tail = t->prev;
      tail->next = NUL;
      delete t;
    } else {
      t->prev->next = t->next;
      t->next->prev = t->prev;
      delete t;
    }
    --size;
  }
  /*
   * @brief search first value x, if found, print "Found"
   */
  void search(int x) {
    Node<Ctx>* t = head;
    int found = 0;
    while (t != NUL) {
      if (t->val == x) {
        std::cout << "\nFound";
        found = 1;
        break;
      }
      t = t->next;
    }
    if (found == 0) { std::cout << "\nNot Found"; }
  }
  /*
   * @brief cout list
   */
  void cout() {
    Node<Ctx>* t = head;
    if (t == NUL) return;
    t->ctx.cout();
    t = t->next;
    while (t != NUL) {
      std::cout << " ";
      t->ctx.cout();
      t = t->next;
    }
    std::cout << "\n";
  }
  /*
   * @brief Reverse cout list
   */
  void reverseShow() {
    Node<Ctx>* t = head;
    while (t != NUL && t->next != NUL) { t = t->next; }
    while (t != NUL) {
      std::cout << t->val << "\t";
      t = t->prev;
    }
  }
 public:
};
class Ctx {
 public:
  Ctx() {}
  Ctx(int val) : val(val) {}
  Ctx(const Ctx& other) { val = other.val; }
  Ctx(Ctx&& other) { val = other.val; }
  void cout() { std::cout << val; }
  int val;
};
template<typename TDList>
bool remove_continue(int& cnt, TDList&& lst) {
  using TCtx = decltype(lst.head->ctx);
  Node<TCtx>* t = lst.head;
  bool tri = false;
  // 先去掉所有連續的
  while (t != NUL) {
    // 連續的出現
    if (t->next != NUL && t->ctx.val == t->next->ctx.val) {
      tri = true;
      cnt++;
      lst.remove(t);
      lst.remove(t->next);
    } else {
      t = t->next;
    }
  }
  return tri;
}
// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(NUL) {}
  ListNode(int x) : val(x), next(NUL) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;
    stack<ListNode*> stk;
    ListNode* k = head;
    ListNode* new_head = NUL;
    while (k) {
      if (!k->next) {
        new_head = k;
        break;
      }
      stk.push(k);
      k = k->next;
    }
    while (!stk.empty()) {
      ListNode* k1 = stk.top();
      stk.pop();
      k1->next->next = k1;
      k1->next = NUL;
    }
    return new_head;
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NUL);
  DList<Ctx> lst;
  lst.insert_tail(Ctx(1));
  lst.insert_tail(Ctx(2));
  lst.insert_tail(Ctx(3));
  lst.insert_tail(Ctx(3));
  lst.insert_tail(Ctx(1));
  lst.insert_tail(Ctx(2));
  lst.cout();
  int cnt = 0;
  lst.cout();
  std::cout << cnt << "\n";
  return 0;
}
