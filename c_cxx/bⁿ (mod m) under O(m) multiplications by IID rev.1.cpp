/* If b = m∙q + r, where m, q ∈ ‌ℤ
	⇒ b ≡ r (mod m)

	⇒ When n ∈ (ℕ ∩ 0),
	b ^ n = (m∙q + r) ^ n
	= ∑[k=0; n]( C[n,k] ∙ (m∙q)^k ∙ r^(n-k) )
		(by the binomial theorem / 二項式定理)
	≡ C[n,0] ∙ (m∙q)^0 ∙ r^(n-0)  (mod m)
	= 1 ∙ 1 ∙ r^n
	= r ^ n
	
∴ If b ≡ r (mod m), b ^ n ≡ r ^ n (mod m)

There're up to m possible c's in [0,|m|)
  in this equation:
	b ^ n ≡ c (mod m).

Because
	b ^ (n+1) = b ^ n ∙ b ≡ c ∙ b (mod m),
  we can find that every b ^ (n+1) can be
  determined uniquely by only b ^ n (mod m)
  no matter which number the n is.

Consequently, while n increasing,
  the appearance of the different values of c 
  will become a repeated pattern at some point
  before n larger than |m|.

Therefore, we can find the smallest non-negative c,
  that meets the equation, b ^ n ≡ c (mod m),
  and only need to calculate
  the first fews (no more than |m|) values of 2 ^ n.
*/


/* input: "base exp mdl<ENTER>", where
	  base is a long long int,
	  exp is a unsigned long long int,
	  mdl is a nonzero long int.
	output: the remainder of
	  base ^ exp divided by mdl.
	Time complexty of the best case (estimated):
	  O(1) multiplications
	Worst case (estimated):
	  O(mdl) multiplications
	Space complexty: O(mdl)   */


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
	long long obase, base;
	unsigned long long exp, step, emSize;
	long omdl, mdl, res, ccBegin, ccLength;
	vector<long> em;
	vector<bool> vst;
	
	cin>> obase>> exp>> omdl;
	mdl = omdl;
	if (mdl<0){mdl*=-1;}
	step = min(exp+1, (unsigned long long)mdl);
	em.assign(step, -1);
	vst.assign(mdl, false);
	
	base = obase % mdl;
	if (base<0){base+=mdl;}

	cout<< "The base "<< obase<< " is congruent to "<< base
	  << " (mod "<< omdl<< ")\n\n";

	for (emSize=0, res=1; !(vst[res]) && emSize<step; ++emSize, res = res*base % mdl){
		em[emSize] = res;
		vst[res] = true;
		cout<< obase<< " ^ "<< emSize<<
		  " ≡ ["<< res<< "]"<<
		  " (mod "<< omdl<< ")\n";
	}
	
	vst.clear();
	
	ccBegin = find(em.begin(), em.end(), res) - em.begin();
	ccLength = emSize-ccBegin;
	
	em.resize(emSize);
	
	cout<< '\n';
	if (ccBegin<emSize){
		cout<< "Circulation Head: "<<
		  obase<< " ^ "<< ccBegin<<
		  " ≡ ["<< em[ccBegin]<< "]"<<
		  " (mod "<< omdl<< ")\n"<<
		  "Circulation End: "<<
		  obase<< " ^ "<< emSize<<
		  " ≡ ["<< (em.back()*base % mdl)<< "]"<<
		  " (mod "<< omdl<< ")\n"<<
		  "Circulation Length: "<< ccLength<< '\n';
	} else {
		cout<< "No circulation ends reached.\n";
	}
	
	long long resIndex;
	if (exp>=ccBegin){
		resIndex = (exp - ccBegin) % ccLength + ccBegin;
	} else {
		resIndex = exp;
	}
	res = em[resIndex];
	
	cout<< obase<< " ^ "<< exp<<
	  " ≡ ["<< res<< "]"<<
	  " (mod "<< omdl<< ")\n";
	
	em.clear();
	
	return 0;
}

// By Iep Iweidieng (葉威呈) at January, 19, 2018 (Fri.) (Fri.)
