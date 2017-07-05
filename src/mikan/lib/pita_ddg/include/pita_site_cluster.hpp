#ifndef PITA_SITE_CLUSTER_HPP_
#define PITA_SITE_CLUSTER_HPP_

#include <pita_score.hpp>         // PITADDGScores
#include <pita_seed_site.hpp>     // PITASeedSites
#include <set>                    // set
#include <map>                    // multimap
#include <utility>                // pair

namespace ptddg {

template<class TRNAString>
class PITASiteCluster {
public:
    // Define methods
    PITASiteCluster() : mSiteCount(0) {}

    std::set<unsigned> &get_mrna_pos_set() { return mRNAPosSet; }

    std::multimap<unsigned, unsigned> &get_mrna_pos_map() { return mSiteMap; }

    int get_site_count() { return mSiteCount; }

    // Method prototype
    void clear_cluster();

    void cluster_site_pos(PITASeedSites <TRNAString> &pSeedSites);

private:
    typedef std::pair<unsigned, unsigned> TPosPair;

    int mSiteCount;
    std::set<unsigned> mRNAPosSet;
    std::multimap<unsigned, unsigned> mSiteMap;

};

//
// Identify overlapped sites
//
template<class TRNAString>
class PITAOverlap {
public:
    // Define methods
    PITAOverlap() {}

    // Method prototype
    int filter_overlapped_sites(PITASeedSites <TRNAString> &pSeedSites, int pGapLen);

    void clear_cluster();

private:
    typedef std::set<unsigned>::iterator TItSet;
    typedef std::multimap<unsigned, unsigned>::iterator TItMap;
    typedef std::pair<TItMap, TItMap> TItRetPair;
    typedef std::multimap<unsigned, unsigned>::iterator TITStartPos;
    typedef std::pair<unsigned, unsigned> TPosPair;

    PITASiteCluster<TRNAString> mSiteCluster;

private:
    void mark_overlapped_sites(PITASeedSites <TRNAString> &pSeedSites, int pPrevIdx, int pCurIdx);

    unsigned get_seedtype_precedence(const seqan::CharString &pSeedType);
};

//
// Sort sites by position
//
template<class TRNAString>
class PITASortedSitePos {
public:
    // Define methods
    PITASortedSitePos() {}

    // Method prototype
    int generate_sorted_mrna_pos(PITASeedSites <TRNAString> &pSeedSites);

    const seqan::String<unsigned> &get_sorted_mrna_pos() { return mSortedSitePos; }

    void clear_site_pos();

private:
    typedef std::set<unsigned>::iterator TItSet;
    typedef std::multimap<unsigned, unsigned>::iterator TItMap;
    typedef std::pair<TItMap, TItMap> TItRetPair;
    typedef std::multimap<unsigned, unsigned>::iterator TITStartPos;
    typedef std::pair<unsigned, unsigned> TPosPair;

    seqan::String<unsigned> mSortedSitePos;
    PITASiteCluster<TRNAString> mSiteCluster;

};

} // namespace ptddg

#endif /* PITA_SITE_CLUSTER_HPP_ */
