#include <mikan/lib/targetscan5_cs/include/ts5_inst_template.hpp> // TRNATYPE
#include <mikan/lib/targetscan5_cs/include/ts5_seed_site.hpp>     // TS5Sequences, TS5SeedSeqs, TS5SeedSites
#include <seqan/seq_io.h>

using namespace seqan;

namespace ts5cs{

//
// TS5Sequences methods
//
template <class TRNAString>
int TS5Sequences<TRNAString>::read_fasta(CharString const &pFasta)
{
    CharString id;
    CharString seq;

    SequenceStream seqStream(toCString(pFasta));
    if (!isGood(seqStream))
    {
        std::cerr << "ERROR: Could not open the file!" << std::endl;
        return 1;
    }

    while (!atEnd(seqStream))
    {
        if (readRecord(id, seq, seqStream) != 0)
        {
            std::cerr << "ERROR: Could not read from " << toCString(pFasta) << "!" << std::endl;
            return 1;
        }

        toUpper(seq);
        for (unsigned i = 0; i < length(seq); ++i){
            if (seq[i] == 'T')
            {
                seq[i] = 'U';
            }
        }
        appendValue(mSeqIds, id);
        appendValue(mSeqs, seq);
    }

    return 0;
}

//
// TS5SeedSeqs methods
//
template <class TRNAString>
int TS5SeedSeqs<TRNAString>::create_seed_seqs()
{
    if (length(mMiRNASeq) == 0)
    {
        return 1;
    }

    TRNAString seedSeq;

    resize(seedSeq, 6);
    for (unsigned i = 0; i < length(seedSeq); ++i)
    {
        seedSeq[i] = mMiRNASeq[i+1];
    }
    reverseComplement(seedSeq);

    appendValue(mSeedSeqs, seedSeq);

    return 0;
}

template <class TRNAString>
void TS5SeedSeqs<TRNAString>::set_mirna_seq(TRNAString pSeq)
{
    clear(mSeedSeqs);
    mMiRNASeq = pSeq;
}

//
// TS5SeedSites methods
//
template <class TRNAString, int SEEDLEN>
void TS5SeedSites<TRNAString, SEEDLEN>::reset_finder()
{
    goBegin(mFinder);
    clear(mFinder);
}

template <class TRNAString, int SEEDLEN>
int TS5SeedSites<TRNAString, SEEDLEN>::find_seed_sites(TRNAString const &pMiRNA)
{
    TS5SeedSeqs<TRNAString> seedSeqs;
    TRNAString seedSeq;
    int retVal;

    reset_finder();

    seedSeqs.set_mirna_seq(pMiRNA);
    retVal = seedSeqs.create_seed_seqs();
    if (retVal != 0)
    {
        std::cerr << "ERROR: Could not get the seed sequence for " << pMiRNA;
        std::cerr << "." << std::endl;
        return 1;
    }

    seedSeq = seedSeqs.get_seed_seq();
    while (find(mFinder, seedSeq))
    {
        appendValue(mMRNAPos, position(mFinder).i1);
        appendValue(mSitePos, position(mFinder).i2);
    }

    return 0;
}

template <class TRNAString, int SEEDLEN>
void TS5SeedSites<TRNAString, SEEDLEN>::clear_pos()
{
    clear(mMRNAPos);
    clear(mSitePos);
}

// Explicit template instantiation
template class TS5Sequences<TRNATYPE>;
template class TS5SeedSeqs<TRNATYPE>;
template class TS5SeedSites<TRNATYPE>;

} // namespace ts5cs