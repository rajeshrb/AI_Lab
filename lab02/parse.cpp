#include <string>
#include <cstdio>
#include <stack>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <iomanip>
#include <cmath>

using namespace std;

#define SZ size
#define pb push_back
#define len length
#define VS vector<string>
#define VI vector<int>
#define pp pop
#define tp top
#define ps push
#define em empty
#define PR pair<int,int>
#define STK stack<pair<char,int> >
#define STKS stack<string> 
#define mk make_pair
#define ff first
#define ss second
#define LS list<pair<string,int> >
#define ITR(x) x::iterator
#define BG begin
#define EN end
#define imply "->"
#define DL erase

int no_of_nodes;
VS PLSentence;

/* information about a proposition/axiom/hypothesis */
struct aProposition
{
	int proposition_no;
	int derived_from[2];
	int axioms;					/* 1 for A1, 2 for A2, 3 for A3 */
	bool mp;						/* 0 if modus ponens not used else 1 */
	aProposition(int pos,int* df, int axiom, bool md)
	{
		proposition_no=pos;
		derived_from[0]=df[0];
		derived_from[1]=df[1];
		axioms=axiom;
		mp=md;
	}
};

#define UMP unordered_map<string,aProposition* >
#define IN insert

/* all the steps of the derivation */

UMP allSteps;

/* struct for each node in the tree */
struct PLNode
{
	string nodeVal;
	string WFF;
	int nodeIndex;
	int parentIndex;
	PLNode* lNode;
	PLNode* rNode;
	PLNode(string str, int nIndex): nodeVal(str), nodeIndex(nIndex){}
};

/* parse the paranthesis to seperate the right and left propostions of propositional sentences */
void parse_paranthesis(string logic_sent,PR* bracketpos)
{
	STK paranthesis;
	int sz=logic_sent.len(), i=0,j=0, obrckt=-1, cbrckt=-1, nf=1;
	while(i<sz)
	{
		if(logic_sent[i]=='(')
		{
			paranthesis.ps(mk('(',i));
			nf=0;
		}
		else if(nf && logic_sent[i]=='-')
		{
			bracketpos[j]=mk(obrckt,cbrckt);
			j=1;
			i++;
		}
		else if(logic_sent[i]==')')
		{
			obrckt=paranthesis.tp().ss;
			cbrckt=i;
			paranthesis.pp();
			if(paranthesis.empty())
			{
				bracketpos[j]=mk(obrckt,cbrckt);
				if(j) break;
				j=1;
				i+=2;
			}
		}
		i++;
 	}
}

/* create a syntactic False node */
void createNotNode(PLNode* root)
{
	root->rNode=new PLNode("F",no_of_nodes);
	no_of_nodes++;
	root->rNode->parentIndex=root->nodeIndex;
	root->rNode->lNode=NULL;
	root->rNode->rNode=NULL;
}

/* parse the input string and store it has a binary tree of strings */
PLNode* parse(string & logic_sent)
{
	int sz=logic_sent.len();
	if(sz==0) return NULL;
	else if(sz==1)
	{
		PLNode* root=new PLNode(logic_sent,no_of_nodes);
		no_of_nodes++;
		root->lNode=NULL;
		root->rNode=NULL;
		return root;
	}
	else
	{
		PLNode* root=new PLNode("->",no_of_nodes);
		no_of_nodes++;
		PR bracketpos[]={mk(-1,-1),mk(-1,-1)};
		parse_paranthesis(logic_sent,bracketpos);
		string lstr,rstr="$";
		if(logic_sent[0]=='~')
		{
			root->lNode=new PLNode("->",no_of_nodes);
			root->lNode->parentIndex=root->nodeIndex;
			no_of_nodes++;
			createNotNode(root->lNode);
			if(bracketpos[0].ff!=-1)
			{
				lstr=logic_sent.substr(bracketpos[0].ff+1,bracketpos[0].ss-(bracketpos[0].ff+1));
				root->lNode->lNode=parse(lstr);
				root->lNode->lNode->parentIndex=root->lNode->nodeIndex;
				if(bracketpos[0].ss<sz-1)
				{
					if(logic_sent[bracketpos[0].ss+3]=='~')
					{
						root->rNode=new PLNode("->",no_of_nodes);
						no_of_nodes++;
						createNotNode(root->rNode);
						
						if(bracketpos[1].ff!=-1)
							rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
						else rstr=logic_sent.substr(bracketpos[0].ss+4);
						root->rNode->lNode=parse(rstr);
						root->rNode->lNode->parentIndex=root->rNode->nodeIndex;
					}
					else
					{
						if(bracketpos[1].ff!=-1) rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
						else rstr=logic_sent.substr(bracketpos[0].ss+3);
						root->rNode=parse(rstr);
						root->rNode->parentIndex=root->nodeIndex;
					}
				}
				else root=root->lNode->lNode;
			}
			else 
			{
				lstr=logic_sent.substr(1,1);
				root->lNode->lNode=parse(lstr);
				root->lNode->lNode->parentIndex=root->lNode->nodeIndex;
				if(logic_sent[4]=='~')
				{
					root->rNode=new PLNode("->",no_of_nodes);
					no_of_nodes++;
					createNotNode(root->rNode);
					
					if(bracketpos[1].ff!=-1) rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
					else rstr=logic_sent.substr(5);
					root->rNode->lNode=parse(rstr);
					root->rNode->lNode->parentIndex=root->rNode->nodeIndex;
				}
				else
				{
					if(bracketpos[1].ff!=-1) rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
					else rstr=logic_sent.substr(4);
					root->rNode=parse(rstr);
					root->rNode->parentIndex=root->nodeIndex;
				}
			}
		}
		else
		{
			if(bracketpos[0].ff!=-1)
			{
				lstr=logic_sent.substr(bracketpos[0].ff+1,bracketpos[0].ss-(bracketpos[0].ff+1));
				root->lNode=parse(lstr);
				root->lNode->parentIndex=root->nodeIndex;
				if(bracketpos[0].ss<sz-1)
				{
					if(logic_sent[bracketpos[0].ss+3]=='~')
					{
						root->rNode=new PLNode("->",no_of_nodes);
						no_of_nodes++;
						createNotNode(root->rNode);
						if(bracketpos[1].ff!=-1) rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
						else rstr=logic_sent.substr(bracketpos[0].ss+4);
						root->rNode->lNode=parse(rstr);
						root->rNode->lNode->parentIndex=root->rNode->nodeIndex;
					}
					else
					{
						if(bracketpos[1].ff!=-1) rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
						else rstr=logic_sent.substr(bracketpos[0].ss+3);
						root->rNode=parse(rstr);
						root->rNode->parentIndex=root->nodeIndex;
					}
				}
				else root=root->lNode;
			}
			else
			{
				lstr=logic_sent.substr(0,1);
				root->lNode=parse(lstr);
				root->lNode->parentIndex=root->nodeIndex;
				if(logic_sent[3]=='~')
				{
					root->rNode=new PLNode("->",no_of_nodes);
					no_of_nodes++;
					createNotNode(root->rNode);
					if(bracketpos[1].ff!=-1) rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
					else rstr=logic_sent.substr(4);
					root->rNode->lNode=parse(rstr);
					root->rNode->lNode->parentIndex=root->rNode->nodeIndex;
				}
				else
				{
					if(bracketpos[1].ff!=-1) rstr=logic_sent.substr(bracketpos[1].ff+1,bracketpos[1].ss-(bracketpos[1].ff+1));
					else rstr=logic_sent.substr(3);
					root->rNode=parse(rstr);	
					root->rNode->parentIndex=root->nodeIndex;
				}
			}
		}
		return root;
	}
}

/* compute wff for each node of the wff tree */ 
void wffOfNode(PLNode* tree)
{
	if(tree==NULL) return ;
	else if(tree->lNode==NULL && tree->rNode==NULL)
	{
		tree->WFF=tree->nodeVal;
		return ;
	}
	else
	{
		wffOfNode(tree->lNode);
		wffOfNode(tree->rNode);
		tree->WFF="("+tree->lNode->WFF+imply+tree->rNode->WFF+")";
		return ;
	}
}

/* all hypothesis and deduction of left side of WFF */
void init_hypothesis_steps(PLNode* tree, STKS & stks, int & pos)
{
	if(tree==NULL) return ;
	else if(tree->lNode==NULL && tree->rNode==NULL)
	{
		string str=tree->nodeVal;
		stks.ps(str);
		pos++;
		int df[]={0,0};
		aProposition* prop=new aProposition(pos,df,0,0);
		allSteps.IN(mk(str,prop));
		return ;
	}
	else
	{
		init_hypothesis_steps(tree->lNode,stks,pos);
		init_hypothesis_steps(tree->rNode,stks,pos);
		
		string strr=stks.tp(), strl, str;
		stks.pp();
		strl=stks.tp();
		stks.pp();
		pos++;
		
		str="("+strl+imply+strr+")";
		if(allSteps.find(str)==allSteps.EN())
		{
			int df[2];
			df[0]=allSteps[strl]->proposition_no;
			df[1]=allSteps[strr]->proposition_no;
			aProposition* prop=new aProposition(pos,df,1,1);
			allSteps.IN(mk(str,prop));
		}
		stks.ps(str);
	}
}

/* apply axioms and dedcution theorem */
void deriveSteps(PLNode* tree,int & pos, bool & derived)
{
	if(tree==NULL) ;
	else
	{
		string str=tree->WFF, strl, strr;
		
		/* if the proposition at the node is not present in the proposition so far obtained */
		if(allSteps.find(str)==allSteps.EN())
		{
			PLNode* lnode=tree->lNode, *rnode=tree->rNode;
			
			/* the tree is not leaf */
			if(lnode!=NULL && rnode!=NULL)
			{
				strl=lnode->WFF;
				
				/* if the ltree is leaf */
				if(lnode->lNode==NULL && lnode->rNode==NULL)
				{
					strr=rnode->WFF;
					
					/* if the proposition at the rnode is not present in the proposition so far obtained */ 
					if(allSteps.find(strr)==allSteps.EN())
					{
						
						/* rnode is leaf */
						if(rnode->lNode==NULL && rnode->rNode==NULL)
						{
							string help;
							cout<<"Need some help (a hypothesis would be useful): ";
							int i;
							for(i=0; i<10; i++)
							{
								cin>>help;
								
								/* add code to insert help */
								int df[]={0,0};
								pos++;
								aProposition* prop=new aProposition(pos,df,-1,0);
								allSteps.IN(mk(help,prop));
								if(help==strr)
								{
									/* useful , add code */
									strl="("+strl+imply+help+")";
									df[0]=pos;
									pos++;
									df[1]=pos;
									prop=new aProposition(pos,df,1,1);
									allSteps.IN(mk(strl,prop));
									break;
								}
								else cout<<"Not useful, try again : ";
							}
							if(i==10)
							{
								derived=0;
								return ;
							}
						}
						/* rtree is not leaf */
						else 
						{
							/* derive rtree */
							deriveSteps(rnode,pos,derived);
							if(derived)
							{
								strl="("+strl+imply+strr+")";
								int df[2];
								df[0]=allSteps[strr]->proposition_no;
								pos++;
								df[1]=pos;
								aProposition* prop=new aProposition(pos,df,1,1);
								allSteps.IN(mk(strl,prop));
							}
						}
					}
					else 
					{
						/* add code for axioms and mp application */
						if(derived)
						{
							strl="("+strl+imply+strr+")";
							int df[2];
							df[0]=allSteps[strr]->proposition_no;
							pos++;
							df[1]=pos;
							aProposition* prop=new aProposition(pos,df,1,1);
							allSteps.IN(mk(strl,prop));
						}
					}
				}
				/* ltree is not leaf */
				else
				{
					if(allSteps.find(strl)==allSteps.EN()) deriveSteps(lnode,pos,derived);
					if(derived)
					{
						strr=rnode->WFF;
						/* if the proposition at the lnode is not present in the proposition so far obtained */ 
						if(allSteps.find(strr)==allSteps.EN())
						{
							/* rnode is leaf */
							if(rnode->lNode==NULL && rnode->rNode==NULL)
							{
								string help;
								cout<<"Need some help (a hypothesis would be useful): ";
								int i;
								for(i=0; i<10; i++)
								{
									cin>>help;
									/* add code to insert help */
									int df[]={0,0};
									pos++;
									aProposition* prop=new aProposition(pos,df,-1,0);
									allSteps.IN(mk(help,prop));
									if(help==strr)
									{
										/* useful , add code */
										strl="("+strl+imply+help+")";
										df[0]=pos;
										pos++;
										df[1]=pos;
										prop=new aProposition(pos,df,1,1);
										allSteps.IN(mk(strl,prop));
										break;
									}
								}
								if(i==10)
								{
									derived=0;
									return ;
								}
							}
							/* rtree is not leaf */
							else 
							{
								/* derive rtree */
								deriveSteps(rnode,pos,derived);
								if(derived)
								{
									strl="("+strl+imply+strr+")";
									int df[2];
									df[0]=allSteps[strr]->proposition_no;
									pos++;
									df[1]=pos;
									aProposition* prop=new aProposition(pos,df,1,1);
									allSteps.IN(mk(strl,prop));
								}
							}
						}
						else 
						{
							/* add code for axioms and mp application */
							if(derived)
							{
								strl="("+strl+imply+strr+")";
								int df[2];
								df[0]=allSteps[strr]->proposition_no;
								pos++;
								df[1]=pos;
								aProposition* prop=new aProposition(pos,df,1,1);
								allSteps.IN(mk(strl,prop));
							}
						}
					}
				}
			}
			else return ;
		}
	}
}

void removeSteps(PLNode* tree)
{
	for(PLNode* p=tree; p!=NULL; p=p->rNode)
		if(p->WFF.len()>1) allSteps.DL(p->WFF);
}

/* print the propositional sentence from the parse tree */
void printPLtree(PLNode* root)
{
	if(root==NULL) return ;
	else
	{
		cout<<root->WFF<<endl;
		printPLtree(root->lNode);
		printPLtree(root->rNode);
		return ;
	}
}

/* main function to call for I/O */
int main()
{
	string logic_sent;
	PLNode* root;
	bool derived=1;
	cin>>logic_sent;
	no_of_nodes=0;
	root=parse(logic_sent);
	STKS stks;
	no_of_nodes=0;
	wffOfNode(root);
	init_hypothesis_steps(root->lNode,stks,no_of_nodes);
	deriveSteps(root,no_of_nodes,derived);
	removeSteps(root);
	cout<<endl;
	for(ITR(UMP) it=allSteps.BG(); it!=allSteps.EN(); it++)
	{
		aProposition* prop=it->ss;
		cout<<"("<<prop->proposition_no<<") "<<it->ff;
		int k=3+(log10(prop->proposition_no)+1)+it->ff.len();
		cout<<setw(50-k);
		if(!prop->axioms) cout<<"hypothesis\n";
		else
		{
			if(prop->axioms==1)
			{
				cout<<"axiom A1 on ("<<prop->derived_from[0]<<")";
				if(prop->mp) cout<<", mp";
				cout<<endl;
			}
			else if(prop->axioms==2)
			{
				cout<<"axiom A2 on ("<<prop->derived_from[0]<<")";
				if(prop->mp) cout<<", mp";
				cout<<endl;
			}
			else if(prop->axioms==-1) cout<<"user given hypothesis\n";
		}
	}
	if(!derived) cout<<"Cannot derive steps/prove\n";
	else cout<<"WFF is Proveable\n";
	return 0;
}