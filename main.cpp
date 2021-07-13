#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct node
{
  struct node *left;
  int data;
  struct node *right;
}*root=NULL;
//root is globally accessible


void insert(int key)
{
    struct node *t=root;
    struct node *r, *p;

    if(t==NULL)
    {
        p=(struct node *)malloc(sizeof(struct node));
        p->data=key;
        p->left=p->right=NULL;
        root=p;
        return;
    }
    while(t)
    {
        r=t;
        if(t->data<key)
        {
            t=t->right;
        }
        else if(t->data>key)
        {
            t=t->left;
        }
        else
            return;
    }
    p=(struct node *)malloc(sizeof(struct node));
    p->data=key;
    p->left=p->right=NULL;

    if(key>r->data)
    {
        r->right=p;
    }
    else
        r->left=p;
}

struct node * recInsert(struct node *p, int key)
{
    struct node *t=NULL;
    if(p==NULL)
    {
        t=(struct node *)malloc(sizeof(struct node));
        t->data=key;
        t->right=t->left=NULL;
        return t;
    }

    else if(p->data > key)
    {
        p->left=recInsert(p->left , key);
    }

    else if(p->data < key)
    {
        p->right=recInsert(p->right, key);
    }

    return p;
}

struct node * search(int key)
{
    struct node *t=root;

    while(t)
    {
        if(t->data==key)
        {
            return t;
        }
        else if(t->data>key)
        {
            t=t->left;
        }
        else if(t->data<key)
        {
            t=t->right;
        }
    }

    return NULL;
}

int height(struct node *p)
{
    int x=0, y=0;
    if(p==NULL)
        return 0;
    x=height(p->left);
    y=height(p->right);
    return x>y?x+1:y+1;
}
struct node * inSucc(struct node *p)
{
    while(p && p->left)
        p=p->left;
    return p;
}

struct node * inPre(struct node *p)
{
    while(p && p->right)
        p=p->right;
    return p;
}

struct node *del(struct node *p, int key)
{
    struct node *q;

    if(p==NULL)
        return NULL;

    if(p->left==NULL && p->right==NULL)
    {
        if(p==root)
            root=NULL;
        free(p);
        return NULL;
    }

    if(key > p->data)
        del(p->right,key);
    else if(key < p->data)
        del(p->right,key);

    else
        if(height(p->left) > height(p->right))
        {
            q=inPre(p->left);
            p->data=q->data;
            p->left=del(p->left, q->data);
        }
        else
        {
            q=inSucc(p->right);
            p->data=q->data;
            p->right=del(p->right, q->data);
        }
    return p;
}

void Inorder(struct node *root)
{
    if(root)
    {
      Inorder(root->left);
      cout<<root->data<<"\t";
      Inorder(root->right);
    }
}

int main()
{
    struct node *temp;
    root=recInsert(root,10);
    recInsert(root,5);
    recInsert(root,30);
    recInsert(root,20);
    recInsert(root,45);
    recInsert(root,80);

    del(root,10);

    Inorder(root);
    cout<<"\n";

    temp=search(80);
    if(temp!=NULL)
        cout<<temp->data<<"  found";
    else
    {
        cout<<"Not found in the BST";
    }

    cout<<"\n\n";
    return 0;
}
