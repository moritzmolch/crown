#ifndef GUARDHHKINFIT_H
#define GUARDHHKINFIT_H
/// The namespace that contains the HHKinFit function.
#include "../include/utility/Logger.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"

#include "../include/HHKinFit/YHKinFitMaster.hxx"

#include "TH1F.h"
#include <math.h> 

namespace hhkinfit {
/**
 * @brief Function to calculate raw fake factors without corrections with
 * correctionlib for the semileptonic channels
 *
 * @param df the input dataframe
 * @param outputname name of the output column for the fake factor
 * @param tau_pt pt of the hadronic tau in the tau pair
 * @param njets number of good jets in the event
 * @param lep_mt transverse mass of the leptonic tau in the tau pair
 * @param nbtags number of good b-tagged jets in the event
 * @param variation name of the uncertainty variation or nominal
 * @param ff_file correctionlib json file with the fake factors
 * @returns a dataframe with the fake factors
 */
auto single_output(const int &idx) {
    return [idx](const ROOT::RVec<float> &result) {
        return result[idx];
    };
};
/**
 * @brief Function to calculate raw fake factors without corrections with
 * correctionlib for the semileptonic channels
 *
 * @param df the input dataframe
 * @param outputname name of the output column for the fake factor
 * @param tau_pt pt of the hadronic tau in the tau pair
 * @param njets number of good jets in the event
 * @param lep_mt transverse mass of the leptonic tau in the tau pair
 * @param nbtags number of good b-tagged jets in the event
 * @param variation name of the uncertainty variation or nominal
 * @param ff_file correctionlib json file with the fake factors
 * @returns a dataframe with the fake factors
 */
ROOT::RDF::RNode
YHKinFit(ROOT::RDF::RNode df, const std::string &outputname_1, const std::string &outputname_2,
                        const std::string &outputname_3, const std::string &outputname_4,
                        const std::string &outputname_5, const std::string &outputname_6,
                        const std::string &outputname_7, const std::string &outputname_8,
                        const std::string &outputname_9,
                        const std::string &tau_pt_1, const std::string &tau_eta_1,
                        const std::string &tau_phi_1, const std::string &tau_mass_1,
                        const std::string &tau_pt_2, const std::string &tau_eta_2,
                        const std::string &tau_phi_2, const std::string &tau_mass_2,
                        const std::string &b_pt_1, const std::string &b_eta_1,
                        const std::string &b_phi_1, const std::string &b_mass_1,
                        const std::string &b_pt_2, const std::string &b_eta_2,
                        const std::string &b_phi_2, const std::string &b_mass_2,
                        const std::string &met, const std::string &met_phi,
                        const std::string &met_cov00, const std::string &met_cov01,
                        const std::string &met_cov10, const std::string &met_cov11,
                        const std::string &YDecay) {
    Logger::get("YHKinFit")
        ->debug("Fitting bbtautau system to get estimation for X mass.");
  
    auto kin_fit = [YDecay](const float &tau_pt_1, const float &tau_eta_1, 
                    const float &tau_phi_1, const float &tau_mass_1, 
                    const float &tau_pt_2, const float &tau_eta_2, 
                    const float &tau_phi_2, const float &tau_mass_2, 
                    const float &b_pt_1, const float &b_eta_1, 
                    const float &b_phi_1, const float &b_mass_1, 
                    const float &b_pt_2, const float &b_eta_2, 
                    const float &b_phi_2, const float &b_mass_2, 
                    const float &met, const float &met_phi, 
                    const float &met_cov00, const float &met_cov01, 
                    const float &met_cov10, const float &met_cov11) {
        auto kinfit_mX = -10.;
        auto kinfit_mY = -10.;
        auto kinfit_mh = -10.;
        auto kinfit_chi2 = 999.;
        auto kinfit_prob = 0.;
        auto kinfit_pull1 = -10.;
        auto kinfit_pull2 = -10.;
        auto kinfit_pullBalance = -10.;
        auto kinfit_convergence = -1.;

        if ((tau_pt_1 > 0.) && (tau_pt_2 > 0.) && (b_pt_1 > 0.) && (b_pt_2 > 0.)) {
            ROOT::Math::PtEtaPhiMVector tau_1 = ROOT::Math::PtEtaPhiMVector(tau_pt_1, tau_eta_1, tau_phi_1, tau_mass_1);
            ROOT::Math::PtEtaPhiMVector tau_2 = ROOT::Math::PtEtaPhiMVector(tau_pt_2, tau_eta_2, tau_phi_2, tau_mass_2);
            ROOT::Math::PtEtaPhiMVector b_1 = ROOT::Math::PtEtaPhiMVector(b_pt_1, b_eta_1, b_phi_1, b_mass_1);
            ROOT::Math::PtEtaPhiMVector b_2 = ROOT::Math::PtEtaPhiMVector(b_pt_2, b_eta_2, b_phi_2, b_mass_2);

            ROOT::Math::PtEtaPhiMVector met_LV = ROOT::Math::PtEtaPhiMVector(met, 0., met_phi, 0.);
            TMatrixD met_cov(2, 2);
            met_cov[0][0] = met_cov00;
            met_cov[1][0] = met_cov10;
            met_cov[0][1] = met_cov01;
            met_cov[1][1] = met_cov11;

            std::vector<int> hypo_mh = {125};
            // std::vector<int> hypo_mh = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,125,130,140,150,180,210,240,270,300,330,360,390,420,450,480,510,540,570,600,630,660,690,720,750,780,810,840,870,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000};
            std::vector<int> hypo_mY = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,125,130,140,150,180,210,240,270,300,330,360,390,420,450,480,510,540,570,600,630,660,690,720,750,780,810,840,870,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000};
            bool YToTauTau = false;
            if (YDecay=="YToTauTau") {
                YToTauTau = true;
            } 

            YHKinFitMaster kinFits = YHKinFitMaster(b_1, b_2, tau_1, tau_2, met_LV, met_cov, YToTauTau);
            kinFits.addMhHypothesis(hypo_mh);
            kinFits.addMYHypothesis(hypo_mY);

            kinFits.doFullFit();    

            std::pair<int, int> bestHypo = kinFits.getBestHypoFullFit();
            Logger::get("YHKinFit")
                ->debug("best hypothesis: H->tautau {}, H->bb {}", bestHypo.first, bestHypo.second);    

            if(bestHypo.second>0) {
                std::map< std::pair<int, int>, double> fit_results_chi2 = kinFits.getChi2FullFit();
                std::map< std::pair<int, int>, double> fit_results_fitprob = kinFits.getFitProbFullFit();
                std::map< std::pair<int, int>, double> fit_results_mX = kinFits.getMXFullFit();
                std::map< std::pair<int, int>, double> fit_results_mY = kinFits.getMYFullFit();
                std::map< std::pair<int, int>, double> fit_results_mh = kinFits.getMhFullFit();
                std::map< std::pair<int, int>, double> fit_results_pull_b1 = kinFits.getPullB1FullFit();
                std::map< std::pair<int, int>, double> fit_results_pull_b2 = kinFits.getPullB2FullFit();
                std::map< std::pair<int, int>, double> fit_results_pull_balance = kinFits.getPullBalanceFullFit();
                std::map< std::pair<int, int>, int> fit_convergence = kinFits.getConvergenceFullFit();

                kinfit_convergence = fit_convergence.at(bestHypo);
                kinfit_mX = fit_results_mX.at(bestHypo);
                kinfit_mY = fit_results_mY.at(bestHypo);
                kinfit_mh = fit_results_mh.at(bestHypo);
                kinfit_chi2 = fit_results_chi2.at(bestHypo);
                kinfit_prob = fit_results_fitprob.at(bestHypo);
                kinfit_pull1 = fit_results_pull_b1.at(bestHypo);
                kinfit_pull2 = fit_results_pull_b2.at(bestHypo);
                kinfit_pullBalance = fit_results_pull_balance.at(bestHypo);
            } 
            Logger::get("YHKinFit")
                ->debug("kinfit_convergence: {}", kinfit_convergence); 
            Logger::get("YHKinFit")
                ->debug("kinfit_mX: {}", kinfit_mX); 
            Logger::get("YHKinFit")
                ->debug("kinfit_mY: {}", kinfit_mY); 
            Logger::get("YHKinFit")
                ->debug("kinfit_mh: {}", kinfit_mh); 
            Logger::get("YHKinFit")
                ->debug("kinfit_chi2: {}", kinfit_chi2); 
            Logger::get("YHKinFit")
                ->debug("kinfit_prob: {}", kinfit_prob); 
            Logger::get("YHKinFit")
                ->debug("kinfit_pull1: {}", kinfit_pull1); 
            Logger::get("YHKinFit")
                ->debug("kinfit_pull2: {}", kinfit_pull2); 
            Logger::get("YHKinFit")
                ->debug("kinfit_pullBalance: {}", kinfit_pullBalance); 
        }

        ROOT::RVec<float> result = {(float) kinfit_convergence, (float) kinfit_mX, (float) kinfit_mY, (float) kinfit_mh, (float) kinfit_chi2, (float) kinfit_prob, (float) kinfit_pull1, (float) kinfit_pull2, (float) kinfit_pullBalance};
        return result;
    };

    std::string result_vec_name = "HYKinFit_vector_" + YDecay + "_resolved";
    if (outputname_1.find("boosted") != std::string::npos) {
        result_vec_name = "HYKinFit_vector_" + YDecay + "_boosted";
    }
    
    auto df1 = df.Define(result_vec_name, kin_fit,
                        {tau_pt_1, tau_eta_1, tau_phi_1, tau_mass_1, tau_pt_2, tau_eta_2, tau_phi_2, tau_mass_2, b_pt_1, b_eta_1, b_phi_1, b_mass_1, b_pt_2, b_eta_2, b_phi_2, b_mass_2, met, met_phi, met_cov00, met_cov01, met_cov10, met_cov11});
    
    auto df2 = df1.Define(outputname_1, hhkinfit::single_output(0), {result_vec_name});
    auto df3 = df2.Define(outputname_2, hhkinfit::single_output(1), {result_vec_name});
    auto df4 = df3.Define(outputname_3, hhkinfit::single_output(2), {result_vec_name});
    auto df5 = df4.Define(outputname_4, hhkinfit::single_output(3), {result_vec_name});
    auto df6 = df5.Define(outputname_5, hhkinfit::single_output(4), {result_vec_name});
    auto df7 = df6.Define(outputname_6, hhkinfit::single_output(5), {result_vec_name});
    auto df8 = df7.Define(outputname_7, hhkinfit::single_output(6), {result_vec_name});
    auto df9 = df8.Define(outputname_8, hhkinfit::single_output(7), {result_vec_name});
    auto df10 = df9.Define(outputname_9, hhkinfit::single_output(8), {result_vec_name});

    return df10;
}

} // namespace hhkinfit
#endif /* GUARDHHKINFIT_H */