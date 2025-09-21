#include "alluneed.h"
/* Doubly linked list support ins_pos rm_pos rm_pos print
 * Make your ins_pos rm_val */
struct Dlst{
  struct V{
    V(int v):v(v){}
    int v;
    bool operator!=(const V& o)const{return v!=o.v;}
  };
  struct N{
    N(V v):p(NUL),n(NUL),v(v){}
    N* p;N* n;V v;
    void print(){cout << v.v;}
  };
  void ins_pos(int p,int v){ins_pos(p,V(v));}
  N* search_first(V v){
    N* k=h;
    while(k!=NUL&&k->v!=v){k=k->n;}
    return k;
  }
  void rm_first(int v){N* k=search_first(V(v));rm_node(k);}
  N* h;N* t;int sz;
  Dlst():h(NUL),t(NUL),sz(0){}
  Dlst(N* h):h(h),t(h),sz(1){}
  void ins_pos(int p,V v){
    if(p<0)p=0;
    if(p>sz)p=sz;
    N* n=new N(v);
    if (p==0){
      n->p=NUL;n->n=h;
      if(h)h->p=n;
      h=n;
      if(sz==0)t=n;
    } else if(p==sz){
      n->n=NUL;n->p=t;
      if(t)t->n=n;
      t=n;
    }else{
      N* k=h;rep(i, p)k=k->n;
      n->p=k->p;n->n=k;k->p->n=n;k->p=n;
    }
    sz++;
  }
  void rm_node(N* k){
    if(k==NUL)return;
    if(k->p)k->p->n=k->n;
    else h=k->n;
    if(k->n)k->n->p=k->p;
    else t=k->p;
    --sz;
    delete k;
  }
  void rm_pos(int p){
    if(p<0)p=0;
    if(p>=sz)p=sz-1;
    N*k=h;rep(i, p)k=k->n;
    rm_node(k);
  }
  void print(){
    N* t=h;
    if(t == NUL)return;
    t->print();t=t->n;
    while(t != NUL){
      cout<<" ";t->print();t=t->n;
    }
    cout<<"\n";
  }
};
