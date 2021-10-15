#include<bits/stdc++.h>

using namespace std;

struct ListNode{
    int val;
    ListNode *next; 
    ListNode() : val(0), next(nullptr){}
    ListNode(int x) : val(x), next(nullptr){}
    ListNode(int x, ListNode *next) : val(x), next(next){}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
    ListNode* root = new ListNode();
    ListNode* ans = root;
    while(l1!=nullptr && l2!=nullptr){
        if(l1->val < l2->val){
            ans->next = l1;
            l1=l1->next;
        }
        else{
            ans->next = l2;
            l2= l2->next;
        }
        ans=ans->next;
    }
    ans->next = l1?l1:l2;
    return root->next;
}

void printList(ListNode* l){
    cout<<"START:";
    while(l!=nullptr){
        cout<<l->val<<"-->";
        l = l->next;
    }
    cout<<":END"<<"\n\n";
}

void insert(ListNode** root, int val){
    ListNode* temp = new ListNode(val);

    if(*root == NULL)
        *root = temp;
    else{
        ListNode* ptr;
        ptr = *root;
        while(ptr->next != nullptr)
            ptr= ptr->next;
        ptr->next = temp;
    }
}

ListNode* vectToLL(vector<int> vect){
    ListNode* root = nullptr;
    for(int val: vect)
        insert(&root, val);
    return root;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ListNode* root = vectToLL(vector{1,3,5,7});
    ListNode* root2 = vectToLL(vector{2,4,6,8});
    printList(root);
    printList(root2);
    ListNode* result = mergeTwoLists(root, root2);
    printList(result);
    return 0;
}