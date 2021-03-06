/*Copyright (C) 2015 Olivier Delaneau, Halit Ongen, Emmanouil T. Dermitzakis

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "union_data.h"

union_data::union_data() {
	genotype_count = 0;
	phenotype_count = 0;
	covariate_count = 0;
    pvalue_column = 17;
    variant_column = 6;
    phenotype_column = 0;
    rank_column = 10;
    best_column = 17;
    coldspot_count = 0;
    no_of_files = 0;
}

void union_data::clear() {
	sample_count = 0;
	sample_id.clear();
	genotype_count = 0;
	genotype_val.clear();
	genotype_chr.clear();
	genotype_id.clear();
	genotype_start.clear();
	genotype_end.clear();
	phenotype_count = 0;
	phenotype_val.clear();
	phenotype_id.clear();
	phenotype_chr.clear();
	phenotype_start.clear();
	phenotype_end.clear();
	covariate_count = 0;
	covariate_val.clear();
	covariate_id.clear();
    coldspot_bins_p.clear();
    for (int i = 0 ; i < all_coldspots_p.size(); i++) delete all_coldspots_p[i];
    all_coldspots_p.clear();
    genotype_id_to_idx.clear();
    phenotype_id_to_idx.clear();
    coldspot_count = 0;
}

void union_data::clearNotHotspot() {
    sample_count = 0;
    sample_id.clear();
    genotype_count = 0;
    genotype_val.clear();
    genotype_chr.clear();
    genotype_id.clear();
    genotype_start.clear();
    genotype_end.clear();
    phenotype_count = 0;
    phenotype_val.clear();
    phenotype_id.clear();
    phenotype_chr.clear();
    phenotype_start.clear();
    phenotype_end.clear();
    covariate_count = 0;
    covariate_val.clear();
    covariate_id.clear();
    genotype_id_to_idx.clear();
    phenotype_id_to_idx.clear();
}


union_data::~union_data() {
	clear();
}

void union_data::residualizePhenotypes() {
	//vrb.title("Residualize phenotypes for covariates");
	residualizer covariate_engine (sample_count);
	for (int c = 0 ; c < covariate_count ; c ++) covariate_engine.push(covariate_val[c]);
	covariate_engine.build();
	for (unsigned int p = 0 ; p < phenotype_count ; p ++) covariate_engine.residualize(phenotype_val[p]);
	//vrb.bullet("#covariates = " + stb.str(covariate_count));
}
