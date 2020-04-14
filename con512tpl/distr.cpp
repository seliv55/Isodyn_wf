#include <iostream>
#include "nums.hh"
#include "tk.hh"
#include "nv.hh"
#include "modlab.h"
using namespace std;
void Ldistr::distr(double *py,double *pdydt) {
	double NOL=0.;
	setiso(py); setdiso(pdydt);
	for (int i=0;i<Nn;i++) pdydt[i]=0.;
	Problem.ff(py,pdydt);
	Problem.fin(py);/**/
gl.input(pyrc,fluxes[hk]/gl.sumt());
pyrc.output(fluxes[pyrclac]);
lac.input(lacc,fluxes[lacin]/lac.sumt());
lacc.input(pyr,fluxes[laccpyr]);
pyrc.input(lacc,fluxes[pyrclacc]);
pyr.cutfirst(coa,fluxes[pdh]);
cit.icdh(akg,fluxes[citakg]);
akg.decarb(suc,fluxes[akgsuc]);
suc.input(mal,fluxes[sucmal]);
pyr.carb(mal,fluxes[pc]);
mal.decarb(pyr,fluxes[malicm]);
oac.input(mal,fluxes[oacd]);
akgc.input(akg,fluxes[akgdcm]);
cit.split(oac,coa,fluxes[liase]);
akgc.icdhr(cit,fluxes[akgcit1]);
gln.input(akgc,fluxes[gln_in]/gln.sumt());
pyrc.output(fluxes[ala_o]);
cit.condence(coa,mal,fluxes[cs0]);
gl.volume(Vt);
	lac.volume(Vt);
	gln.volume(Vt);
	symm(mal.getisot());
py[npyrc]=pyrc.sumt(); py[npyr]=pyr.sumt(); py[ncoa]=coa.sumt(); py[noac]=oac.sumt(); py[ncit]=cit.sumt(); py[nakg]=akg.sumt(); py[nakgc]=akgc.sumt(); py[nsuc]=suc.sumt(); py[nmal]=mal.sumt(); py[nlacc]=lacc.sumt(); py[ngl]=gl.sumt(); py[nlac]=lac.sumt(); py[ngln]=gln.sumt(); 
//xx[npyrc]=py[npyrc]; xx[npyr]=py[npyr]; xx[ncoa]=py[ncoa]; xx[noac]=py[noac]; xx[ncit]=py[ncit]; xx[nakg]=py[nakg]; xx[nakgc]=py[nakgc]; xx[nsuc]=py[nsuc]; xx[nmal]=py[nmal]; xx[nlacc]=py[nlacc]; xx[ngl]=py[ngl]; xx[nlac]=py[nlac]; xx[ngln]=py[ngln]; 
}
