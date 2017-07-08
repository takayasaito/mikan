#ifndef RH2_SITE_CLUSTER_HPP_
#define RH2_SITE_CLUSTER_HPP_

#include <set>                   // set
#include <map>                   // multimap
#include <utility>               // pair
#include "mk_typedef.hpp"        // TRNATYPE, TCharSet, TRNASet, TIndexQGram, TFinder
#include "rh2_score.hpp"         // RH2MFEScores
#include "rh2_seed_site.hpp"     // RH2SeedSites

namespace rh2mfe {

class RH2SiteCluster {
public:
    // Define methods
    RH2SiteCluster() : mSiteCount(0) {}

    std::set<unsigned> &get_mrna_pos_set() { return mRNAPosSet; }

    std::multimap<unsigned, unsigned> &get_mrna_pos_map() { return mSiteMap; }

    int get_site_count() { return mSiteCount; }

    // Method prototype
    void clear_cluster();

    void cluster_site_pos(RH2SeedSites &pSeedSites, RH2MFEScores &pScores);

private:
    typedef std::pair<unsigned, unsigned> TPosPair;

    int mSiteCount;
    std::set<unsigned> mRNAPosSet;
    std::multimap<unsigned, unsigned> mSiteMap;

};

//
// Identify overlapped sites
//
class RH2Overlap {
public:
    // Define methods
    RH2Overlap() {}

    // Method prototype
    int filter_overlapped_sites(RH2SeedSites &pSeedSites, RH2MFEScores &pScores,
                                seqan::CharString &pOverlapDef);

    void clear_cluster();

private:
    typedef std::set<unsigned>::iterator TItSet;
    typedef std::multimap<unsigned, unsigned>::iterator TItMap;
    typedef std::pair<TItMap, TItMap> TItRetPair;
    typedef std::multimap<unsigned, unsigned>::iterator TITStartPos;
    typedef std::pair<unsigned, unsigned> TPosPair;

    RH2SiteCluster mSiteCluster;

private:
    void find_overlapped_sites(RH2SeedSites &pSeedSites, RH2MFEScores &pScores,
                               int pPosIdx, seqan::CharString &pOverlapDef);

    void cluster_overlapped_sites(RH2SeedSites &pSeedSites,
                                  RH2MFEScores &pScores, std::multimap<unsigned, unsigned> &pStartPos,
                                  seqan::CharString &pOverlapDef);

    void mark_overlapped_sites(RH2SeedSites &pSeedSites, RH2MFEScores &pScores,
                               std::set<unsigned> &pOlCluster, seqan::CharString &pOverlapDef);

    unsigned get_pos_with_best_mfe(RH2MFEScores &pScores, std::set<unsigned> &pOlCluster);

};

//
// Filter sites by the number of sites
//
class RH2TopNScore {
public:
    // Define methods
    RH2TopNScore() : mTopN(0) {}

    // Method prototype
    int filter_sites(RH2SeedSites &pSeedSites, RH2MFEScores &pScores, int pMaxHits);

    void clear_cluster();

private:
    typedef std::set<unsigned>::iterator TItSet;
    typedef std::multimap<unsigned, unsigned>::iterator TItMap;
    typedef std::pair<TItMap, TItMap> TItRetPair;
    typedef std::multimap<float, unsigned>::iterator TITStartScore;
    typedef std::pair<float, unsigned> TScorePair;

    RH2SiteCluster mSiteCluster;
    int mTopN;

private:
    void sort_sites_by_score(RH2MFEScores &pScores, int pPosIdx);

    void mark_non_topn_sites(RH2MFEScores &pScores, std::multimap<float, unsigned> &pSortedSites);


};

//
// Sort sites by position
//
class RH2SortedSitePos {
public:
    // Define methods
    RH2SortedSitePos() {}

    const seqan::String<unsigned> &get_sorted_mrna_pos() { return mSortedSitePos; }

    // Method prototype
    int generate_sorted_mrna_pos(RH2SeedSites &pSeedSites, RH2MFEScores &pScores);

    void clear_site_pos();

private:
    typedef std::set<unsigned>::iterator TItSet;
    typedef std::multimap<unsigned, unsigned>::iterator TItMap;
    typedef std::pair<TItMap, TItMap> TItRetPair;
    typedef std::multimap<unsigned, unsigned>::iterator TITStartPos;
    typedef std::pair<unsigned, unsigned> TPosPair;

    seqan::String<unsigned> mSortedSitePos;
    RH2SiteCluster mSiteCluster;

private:
    void cluster_site_pos(RH2SeedSites &pSeedSites,
                          RH2MFEScores &pScores);

};

} // namespace rh2mfe

#endif /* RH2_SITE_CLUSTER_HPP_ */
