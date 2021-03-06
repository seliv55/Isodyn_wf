#include <iostream>
#include "nr.h"
#include "nums.hh"
#include "modlab.h"
using namespace std;

int Ldistr::getN() {
met[0]->ny=nmet; //cout<<met[0]->ny<<" "<<met[0]->getdescr()<<'\n';
for(int i=1;i<lmet;i++) {met[i]->ny=met[i-1]->ny+met[i-1]->getlen();}// cout<<met[i]->ny<<" "<<met[i]->getdescr()<<'\n';}
metk[0]->ny= met[lmet-1]->ny+met[lmet-1]->getlen();// cout<<metk[0]->ny<<" "<<metk[0]->getdescr()<<'\n';
for(int i=1;i<lmetk;i++) metk[i]->ny=metk[i-1]->ny+metk[i-1]->getlen();//{ cout<<metk[i]->ny<<" "<<metk[i]->getdescr()<<endl;}
return (Nn=metk[lmetk-1]->ny+metk[lmetk-1]->getlen());
}

void Ldistr::setdiso(double *pyinit) {
for(int i=0;i<lmet;i++) met[i]->diso= &pyinit[met[i]->ny]; 
//  glu25.diso= &pyinit[glu.ny];
for(int i=0;i<lmetk;i++) metk[i]->diso= &pyinit[metk[i]->ny];
}

void Ldistr::setiso(double *pyinit) {
for(int i=0;i<(lmet);i++) met[i]->iso= &pyinit[met[i]->ny];
//  glu25.iso= &pyinit[glu.ny];
for(int i=0;i<(lmetk);i++) metk[i]->iso= &pyinit[metk[i]->ny];
}

void Ldistr::sklad(int itime){
 for(int i=0;i<expm0.size();i++) expm0[i]->skladm0(itime);
 for(int i=0;i<expcon.size();i++) expcon[i]->skladc(itime);
 }

int Ldistr::stor(double dist[]){int n(0);
 for(int i=0;i<expm0.size();i++) {n += expm0[i]->exper[0].stormi(&dist[n],ntime);}
 return n;}
 
int Ldistr::getmicon(){ int n=0;//=expcon.size()*(ntime-1);
 for(int i=0;i<expm0.size();i++) for(int j=0;j<expm0[i]->exper.size();j++) { n += expm0[i]->exper[j].getmi()*(ntime-1);}
 return n;}

void Ldistr::massfr() { for(int i=0;i<expm0.size();i++)  expm0[i]->percent();}

double Ldistr::xits(int its) { double xi=0;
for(int i=0;i<expm0.size();i++) xi += expm0[i]-> xits(its);
return xi;}

double Ldistr::xicon(int its) {int itp=its-1; double xi=0;
for(int i=0;i<expcon.size();i++) xi += expcon[i]-> chicon(its); 
return xi;}

int Ldistr::wriconex(string fn) {
//t=1;  glc=t+1; glsd=glc+1;  lacc=glsd+1; lacsd=lacc+1;
  data *b; ofstream fo(fn); int llen=expcon.size();
 fo<<"time "; for(int i=0;i<llen;i++) fo<<expcon[i]->getdescr()<<" sd "; fo<<endl;
 for(int its=0;its<ntime;its++) { fo<<tex[its];
   for(int i=0;i<llen;i++){ b=expcon[i]->getconc();   fo<<" "<<b[its].mean<<" "<<b[its].sd; }
      fo<<"\n";         }
     return llen;}

int Ldistr::wrim0ex(string fn) {
//t=1;  lac=t+1; lacsd=lac+1; glu=lacsd+1; glusd=glu+1; ala=glusd+1; alasd=ala=+1; gly=alasd+1; glysd=gly+1; ser=glysd+1; sersd=ser+1; pro=sersd+1; prosd=pro+1; cit=prosd+1; citsd=cit+1; agl=citsd+1; aglsd=agl+1; asp=aglsd+1; aspsd=asp+1; fum=aspsd+1; fumsd=fum+1; mal=fumsd+1; malsd=mal+1; coa=malsd+1; coasd=coa+1;
  data *b; ofstream fo(fn); int llen=expm0.size();
fo<<"time "; for(int i=0;i<llen;i++) fo<<expm0[i]->getdescr()<<" sd "; fo<<'\n';
   for(int its=0;its<ntime;its++) {  fo<<tex[its]; cout<<"time="<<tex[its];
       for(int i=0;i<llen;i++) for(int j=0;j<expm0[i]->exper.size();j++) {
          b=expm0[i]->exper[j].getexper(its);   fo<<" "<<b[0].mean<<" "<<b[0].sd;  cout<<" "<<b[0].mean<<" "<<b[0].sd; }
      fo<<'\n'; cout<<'\n';         }
return llen;}

void Ldistr::show(ostringstream& fo,double xfin) { fo<<setw(5)<<xfin;
   for(int i=0;i<expm0.size();i++) expm0[i]-> showm0(fo,xfin); fo<<'\n';
}

void Ldistr::showcon(ostringstream& fo,double xfin) { fo<<setw(5)<<xfin;
for(int i=0;i<expcon.size();i++) expcon[i]-> showcon(fo); fo<<'\n';}

void Ldistr::showdescr(ostringstream& fo, vector<Metab*> em0con) { fo<<"time ";
for(int i=0;i<em0con.size();i++) fo<<em0con[i]-> getdescr()<<" "; fo<<'\n';}

double Ldistr::consum() { double sum(0.), sumex(0.), sumx(0.); 
// for(int i=0;i<=lmet;i++) { int j;
//   for(j=0;j<externcon.size();j++) if(met[i]->getdescr()==externcon[j]->getdescr()) {
//                                  externcon.erase(externcon.begin()+j); j=-1; break;}
//     if(j==externcon.size()) sum += met[i]->sumt(); }
 for(int i=0;i<lmet;i++) {sum += met[i]->sumt(); sumx+=xx[i];}
 for(int i=0;i<lmetk;i++) sum += metk[i]->sumt();
 for(int j=0;j<expcon.size();j++) sumex += expcon[j]->sumt(); 
return sum-sumex;}


