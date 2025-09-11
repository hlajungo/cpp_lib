
#include <bits/stdc++.h>
#include <utility>

using namespace std;

template <typename Ctx>
class Node
{
public:
  // explicit Node (Ctx ctx) : ctx (ctx){};
  explicit Node (Ctx&& ctx)
      : ctx (std::forward<Ctx> (ctx)), prev (nullptr), next (nullptr)
  {
  }
  ~Node () {}
  Ctx ctx;
  Node<Ctx>* prev;
  Node<Ctx>* next;
};

/*
 * @brief Doubly linked list
 */
template <typename Ctx>
class DList
{

public:
  explicit DList () : head (nullptr), tail (nullptr), size (0) {}
  explicit DList (Node<Ctx>* head) : head (head), tail (head), size (1) {}

  /*
   * @param ctx the context for new node.
   */
  void
  insert_tail (Ctx&& ctx)
  {
    // empty list
    if (head == nullptr)
    {
      Node<Ctx>* n = new Node<Ctx> (std::forward<Ctx> (ctx));
      n->prev = nullptr;
      n->next = nullptr;
      head = n;
      tail = n;
      size++;
      return;
    }

    Node<Ctx>* n = new Node<Ctx> (std::forward<Ctx> (ctx));
    tail->next = n;
    n->prev = tail;
    n->next = nullptr;

    tail = n;
    size++;
  }

  void
  remove (int x)
  {
    Node<Ctx>* t = head;
    while (t != nullptr && t->val != x)
    {
      t = t->next;
    }
    if (t == nullptr)
    {
      return;
    }
    if (t->prev == nullptr)
    {
      if (t->next == nullptr)
      {
        head = nullptr;
      }
      else
      {
        head = t->next;
        head->prev = nullptr;
      }
    }
    else if (t->next == nullptr)
    {
      t->prev->next = nullptr;
    }
    else
    {
      t->prev->next = t->next;
      t->next->prev = t->prev;
    }
    delete t;
  }

  void
  remove (Node<Ctx>* t)
  {
    if (size == 0 || t == nullptr)
      return;

    if (size == 1)
    {
      head = nullptr;
      tail = nullptr;
      delete t;
    }
    else if (t == head)
    {
      head = t->next;
      head->prev = nullptr;
      delete t;
    }
    else if (t == tail)
    {
      tail = t->prev;
      tail->next = nullptr;
      delete t;
    }
    else
    {
      t->prev->next = t->next;
      t->next->prev = t->prev;
      delete t;
    }

    --size;
  }

  void
  search (int x)
  {
    Node<Ctx>* t = head;
    int found = 0;
    while (t != nullptr)
    {
      if (t->val == x)
      {
        std::cout << "\nFound";
        found = 1;
        break;
      }
      t = t->next;
    }
    if (found == 0)
    {
      std::cout << "\nNot Found";
    }
  }

  void
  cout ()
  {
    Node<Ctx>* t = head;
    if (t == nullptr)
      return;

    t->ctx.cout ();
    t = t->next;
    while (t != nullptr)
    {
      std::cout << " ";
      t->ctx.cout ();
      t = t->next;
    }
    std::cout << "\n";
  }

  void
  reverseShow ()
  {
    Node<Ctx>* t = head;
    while (t != nullptr && t->next != nullptr)
    {
      t = t->next;
    }
    while (t != nullptr)
    {
      std::cout << t->val << "\t";
      t = t->prev;
    }
  }

public:
  Node<Ctx>* head;
  Node<Ctx>* tail;
  size_t size;
};

class Ctx
{
public:
  Ctx () {}
  Ctx (int val) : val (val) {}
  Ctx (const Ctx& other)
  {
    val = other.val;
  }
  Ctx (Ctx&& other)
  {
    val = other.val;
  }
  void
  cout ()
  {
    std::cout << val;
  }
  int val;
};

template <typename TDList>
bool
remove_continue (int& cnt, TDList&& lst)
{
  using TCtx = decltype (lst.head->ctx);
  Node<TCtx>* t = lst.head;

  bool tri = false;
  // 先去掉所有連續的
  while (t != nullptr)
  {
    // 連續的出現
    if (t->next != nullptr && t->ctx.val == t->next->ctx.val)
    {
      tri = true;
      cnt++;
      lst.remove (t);
      lst.remove (t->next);
    }
    else
    {
      t = t->next;
    }
  }
  return tri;
}

int
main ()
{
  ios_base::sync_with_stdio (false);
  cin.tie (nullptr);

  DList<Ctx> lst;
  lst.insert_tail (Ctx (1));
  lst.insert_tail (Ctx (2));
  lst.insert_tail (Ctx (3));
  lst.insert_tail (Ctx (3));
  lst.insert_tail (Ctx (1));
  lst.insert_tail (Ctx (2));

  lst.cout ();
  int cnt = 0;
  lst.cout ();
  std::cout << cnt << "\n";

  return 0;
}
