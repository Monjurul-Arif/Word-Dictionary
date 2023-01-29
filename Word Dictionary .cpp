#include<bits/stdc++.h>
#include<new>
#include <fstream>

using namespace std;
struct node
{
    string word,meaning;
    node *right,*left;

};
struct node *root = NULL,*temp;

int n;
string iWord,iMeaning,src,cut,del,no,line1,line2;

struct node* insert (struct node *root,string key,string item)
{

    if(root==NULL)
    {
        root = new struct node[1];
        root->right = NULL;
        root->left = NULL;
        root->word = key;
        root->meaning = item;
        return root;
    }
    else if(key<root->word)
    {
        root->left = insert(root->left,key,item);
    }
    else
    {
        root->right = insert(root->right,key,item);
    }
    return root;
};
void inorder(struct node *root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        cout<<"Word : "<<root->word<<"  Meaning : "<<root->meaning<<"\n";
        inorder(root->right);
    }
}
void pre_order(struct node *root)
{

    if(root!=NULL)
    {

        cout<<"Word : "<<root->word<<"  Meaning : "<<root->meaning<<"\n";
        pre_order(root->left);
        pre_order(root->right);
    }

}
void post_order(struct node *root)
{
    if(root!=NULL)
    {
        post_order(root->left);
        post_order(root->right);
        cout<<"Word : "<<root->word<<"  Meaning : "<<root->meaning<<"\n";
    }
}

void order(struct node *root,string no,int M)
{
    if(root!=NULL)
    {
        int f=0;
        for(int i=0;i<M;i++)
        {
            if(no[i]==root->word[i])
            {
               f++;
            }
        }
        if(f==M-2 || f==M-1 || f==M)
        {
           cout<<"Word : "<<root->word<<"  Meaning : "<<root->meaning<<"\n";
        }

        order(root->left,no,M);
        order(root->right,no,M);
    }
}


struct node* searching(struct node *root,string src)
{

    if(root==NULL || root->word==src)
    {
        return root;
    }
    if(src>root->word)
    {
        return searching(root->right,src);
    }
    else
        return searching(root->left,src);
}




struct node* maximum(struct node *root)
{
    if(root->left == NULL)
    {
        return root;
    }
    else
        return maximum(root->left);
};

struct node* minimum(struct node *root)
{
    if(root->right == NULL)
    {
        return root;
    }
    else
        return minimum(root->right);
};




struct node *Delete (struct node * root, string del,string dm)
{


    if(root == NULL)
    {
        return  root;
    }
    if(del < root->word)
    {
        root->left =  Delete (root->left , del , dm);
    }
    if(del > root->word)
    {
        root->right=  Delete (root->right , del , dm);
    }
    else
    {
        // case 1: no child
        if (root ->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return root;
        }
                // case 2: one child
        else if (root ->left == NULL )
        {
            struct node *temp = root;
            root = root->right;
            delete temp;
            return root;
        }
        else if(root ->right == NULL )
        {
            struct node *temp = root;
            root = root->left;
            delete temp;
            return root;
        }
            //case 3:two child
        else
        {
            int m;
            cout<<"Press 1 to make Left Max at root or Press 2 to make Right Min at root : ";
            cin>>m;
            if(m==1)
            {
                struct node *temp = maximum( root->left);
                root->word = temp->word;
                root->meaning=temp->meaning;
                root->left = Delete (root->left, temp->word,temp->meaning);
                return root;
            }

           if(m==2)
            {
            struct node *temp = minimum( root->right);
            root->word = temp->word;
            root->meaning=temp->meaning;
            root->right = Delete (root->right, temp->word,temp->meaning);
            return root;
            }

        }

    }
    return root;

}


int main()
{



    int n,op,ch;


    for(;;)
    {
        cout<<"\n1. Insert word\n";
        cout<<"\n2. Other operation\n";
        cout<<"\n0. Exit from operation\n";

        cout<<"\nEnter a choice : ";
        cin>>ch;

        if(ch==1)
        {
            cout<<"Number of inputs : ";
            cin>>n;
            cout<<endl;
            ofstream outfile;
            outfile.open("afile.txt",ios::out|ios::app);
            for(int i=0; i<n; i++)
            {

                    cout<<"Enter word : ";
                    cin>>iWord;
                    cout<<"Enter meaning : ";
                    cin>>iMeaning;
                    cout<<endl;


                    root=insert(root,iWord,iMeaning);
                    outfile << iWord <<"         "<< iMeaning << endl;


            }
            outfile.close();
        }

        if(ch==2)
        {
            cout<<"1. Inorder print\n";
            cout<<"2. Preorder print\n";
            cout<<"3. Postorder print\n";
            cout<<"4. Search a word\n";
            cout<<"5. Maximun lengthy word\n";
            cout<<"6. Minimum lengthy word\n";
            cout<<"7. Delete a word\n";

            cin>>op;

            switch(op)
            {

            case 1:
                {

                    cout<<endl;
                    cout<<"Inorder : ";
                    inorder(root);
                    cout<<endl;
                    break;
                }

            case 2:
                {
                    cout<<endl;
                    cout<<"PreOrder : ";
                    pre_order(root);
                    cout<<endl;

                    break;
                }

            case 3:
                {
                    cout<<endl;
                    cout<<"PostOrder : ";
                    post_order(root);
                    cout<<endl;

                    break;
                }

            case 4:
                {

                    cout<<"Enter the number u want to search : ";
                    cin>>src;
                    if(searching(root,src)!=NULL)
                {
                    cout<<src<<" was found\n";
                    cout<<"Word:"<<src<<endl;
                    cout<<"Meaning:"<<root->meaning<<endl;
                }
                else
                {
                    cout<<src<<" wasn't found\n\n";
                    cout<<"Similar word : \n";
                    int M = src.size();
                    order(root,src,M);
                    cout<<endl;

                }
                break;
                }

            case 5:
                {

                    temp = maximum(root);
                    cout<<"Maximum length word : "<<temp->word<<endl;

                    break;
                }

            case 6:
                {

                    temp = minimum(root);
                    cout<<"Minimum length word : "<<temp->word<<endl;

                    break;
                }

            case 7:
                {

                    cout<<"Enter the word you want to delete :";
                    cin>>cut;

                    Delete(root,cut,iMeaning);

                    break;
                }

            }


        }


        if(ch==0)
        {
            exit(0);
        }



    }


}



