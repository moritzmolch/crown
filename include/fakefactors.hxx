#ifndef GUARDFAKEFACTORS_H
#define GUARDFAKEFACTORS_H

namespace fakefactors {

ROOT::RDF::RNode raw_fakefactor_nmssm_lt(ROOT::RDF::RNode df, const std::string &outputname,
                                const std::string &tau_pt, const std::string &njets,
                                const std::string &lep_mt, const std::string &nbtags,
                                const std::string &variation, const std::string &ff_file);
ROOT::RDF::RNode fakefactor_nmssm_lt(ROOT::RDF::RNode df, const std::string &outputname,
                                const std::string &tau_pt, const std::string &njets,
                                const std::string &lep_mt, const std::string &nbtags,
                                const std::string &lep_pt, const std::string &lep_iso, 
                                const std::string &variation,
                                const std::string &ff_file, const std::string &ff_corr_file);
} // namespace fakefactors
#endif /* GUARDFAKEFACTORS_H */