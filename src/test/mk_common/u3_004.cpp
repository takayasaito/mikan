#include <iostream>
#include "gtest/gtest.h"
#include "test_io.hpp"
#include "mr3_core.hpp"

namespace {

    class U3004 : public TestIOCommon
    {
    protected:
        U3004() {
            IFNAME1 = (char *)"mir_001.fasta";
            IFNAME2 = (char *)"utr3_004.fasta";
        }
    };

    TEST_F(U3004, mrna_fasta) {
        read_files();
        mrna_ids = coreInput.get_mrna_ids();
        mrna_seqs = coreInput.get_mrna_seqs();

        EXPECT_EQ(5u, length(mrna_ids));

        const char *id1 = "hg18_refGene NM_004817 range=chr9:71059111-71059938 5'pad=0 3'pad=0 "
                "revComp=FALSE strand=+ repeatMasking=none";
        EXPECT_STREQ(id1, seqan::toCString(mrna_ids[0]));

        const char *id2 = "hg18_refGene NM_014481 range=chrX:55050594-55050936 5'pad=0 3'pad=0 "
                "revComp=FALSE strand=+ repeatMasking=none";
        EXPECT_STREQ(id2, seqan::toCString(mrna_ids[1]));

        const char *id3 = "hg18_refGene NM_000183 range=chr2:26366326-26366836 5'pad=0 3'pad=0 "
                "revComp=FALSE strand=+ repeatMasking=none";
        EXPECT_STREQ(id3, seqan::toCString(mrna_ids[2]));

        const char *id4 = "hg18_refGene NM_022365 range=chr10:22085484-22085621 5'pad=0 3'pad=0 "
                "revComp=TRUE strand=- repeatMasking=none";
        EXPECT_STREQ(id4, seqan::toCString(mrna_ids[3]));

        const char *id5 = "hg18_refGene NM_006410 range=chr11:20361328-20361905 5'pad=0 3'pad=0 "
                "revComp=FALSE strand=+ repeatMasking=none";
        EXPECT_STREQ(id5, seqan::toCString(mrna_ids[4]));

        EXPECT_EQ(5u, length(mrna_seqs));
        const char *seq1 = "AUGUCUGAGCACGGACUCUCCCAGGCCUGCCUGCAUGGCAUCAGACUAGC"
                "CACUCCUGCCAGGCCGCCGGGAUGGUUCUUCUCCAGUUAGAAUGCACCAU"
                "GGAGACGUGGUGGGACUCCAGCUCGUGUGUCCUCAUGGAGAACCCAGGGG"
                "ACAGCUGGUGCAAAUUCAGAACUGAGGGCUCUGUUUGUGGGACUGGGUUA"
                "GAGGAGUCUGUGGCUUUUUGUUCAGAAUUAAGCAGAACACUGCAGUCAGA"
                "UCCUGUUACUUGCUUCAGUGGACCGAAAUCUGUAUUCUGUUUGCGUACUU"
                "GUAAUAUGUAUAUUAAGAAGCAAUAACUAUUUUUCCUCAUUAAUAGCUGC"
                "CUUCAAGGACUGUUUCAGUGUGAGUCAGAAUGUGAAAAAGGAAUAAAAAA"
                "UACUGUUGGGCUCAAACUAAAUUCAAAGAAGUACUUUAUUGCAACUCUUU"
                "UAAGUGCCUUGGAUGAGAAGUGUCUUAAAUUUUCUUCCUUUGAAGCUUUA"
                "GGCAGAGCCAUAAUGGACUAAAACAUUUUGACUAAGUUUUUAUACCAGCU"
                "UAAUAGCUGUAGUUUUCCCUGCACUGUGUCAUCUUUUCAAGGCAUUUGUC"
                "UUUGUAAUAUUUUCCAUAAAUUUGGACUGUCUAUAUCAUAACUAUACUUG"
                "AUAGUUUGGCUAUAAGUGCUCAAUAGCUUGAAGCCCAAGAAGUUGGUAUC"
                "GAAAUUUGUUGUUUGUUUAAACCCAAGUGCUGCACAAAAGCAGAUACUUG"
                "AGGAAAACACUAUUUCCAAAAGCACAUGUAUUGACAACAGUUUUAUAAUU"
                "UAAUAAAAAGGAAUACAUUGCAAUCCGU";
        EXPECT_STREQ(seq1, seqan::toCString((seqan::CharString)mrna_seqs[0]));

        const char *seq2 = "ACCAAUGGAGGCCUGGGGACAUCUGGCAUGGUCACCCCUGCACAUGAUCU"
                "GAGGCCAGCUCCCCUUCCCUGAGCUGCCUCCUGCUUCUCCCUCAAAGUCU"
                "CCUACCCUUCUCUUCCUCUUUUAAGCCCUCUCUUCCUCGCUUUCCUUCCU"
                "ACCUAGCUCCUUGUUGGUGAGCUUCUUGUGCCUUAAUCCUGUGACCCAGC"
                "CCCUUACACCACUUUCCACCUUCCUGUCCGAAGUACACGGACACUAGCUG"
                "CCCCAGGAAGUUGUGUGAUUUUAAAUCACUUCUGUCUUUGCUGGAAAGUG"
                "UAUUUGUGCAUAAAUAAAGUCUGUGUAUUUGUUUCAGGGUUGC";
        EXPECT_STREQ(seq2, seqan::toCString((seqan::CharString)mrna_seqs[1]));

        const char *seq3 = "UAGAUCCAGAAGAAGUGACCUGAAGUUUCUGUGCAACACUCACACUAGGC"
                "AAUGCCAUUUCAAUGCAUUACUAAAUGACAUUUGUAGUUCCUAGCUCCUC"
                "UUAGGAAAACAGUUCUUGUGGCCUUCUAUUAAAUAGUUUGCACUUAAGCC"
                "UUGCCAGUGUUCUGAGCUUUUCAAUAAUCAGUUUACUGCUCUUUCAGGGA"
                "UUUCUAAGCCACCAGAAUCUCACAUGAGAUGUGUGGGUGGUUGUUUUUGG"
                "UCUCUGUUGUCACUAAAGACUAAAUGAGGGUUUGCAGUUGGGAAAGAGGU"
                "CAACUGAGAUUUGGAAAUCAUCUUUGUAAUAUUUGCAAAUUAUACUUGUU"
                "CUUAUCUGUGUCCUAAAGAUGUGUUCUCUAUAAAAUACAAACCAACGUGC"
                "CUAAUUAAUUAUGGAAAAAUAAUUCAGAAUCUAAACACCACUGAAAACUU"
                "AUAAAAAAUGUUUAGAUACAUAAAUAUGGUGGUCAGCGUUAAUAAAGUGG"
                "AGAAAUAUUGG";
        EXPECT_STREQ(seq3, seqan::toCString((seqan::CharString)mrna_seqs[2]));

        const char *seq4 = "AUAUUCUGGGAGAUGAUGUUCACCUUCAUUUUCCAAAAUGAAUAUCUUAA"
                "AAAUCUUAUGCAGAAAUUUGCAUUUUGUACCUCAAUAUUUCUACGUCAUG"
                "UGCCUUAGUAAAAAAAAAUAAUAAAUAAAUAAAAGAUG";
        EXPECT_STREQ(seq4, seqan::toCString((seqan::CharString)mrna_seqs[3]));

        const char *seq5 = "CCACAUUGGAGAAAUGGUUUUUAUUGUCAACCUUAACACCCAUCACCAAA"
                "UCGGUAAUUUCAGGGUCUAAAAAAAGUCAGCAUGUUUUAACUUUGUUGUU"
                "UUACUAUCCUCAGGCAUCCAUUCCAAUCAAGAAAUGAUGGUGCUCUGCAU"
                "CAGUGGUUCAGAGCCUGGUUAUACAUAUAGAUCACUCAGGGAGCUUUGGA"
                "AAAAUAAAGAUUUGUCAGCCCUAUCUCAAACUUGAAUCAAAAUUUCUGGG"
                "GUGUGGGCACAAUAAUCUGUAAUUUUCUUUGUUUAUACUUCCCCUGAUGC"
                "CACUGGUUCCGAUGCCACUGGCUGGGGGGCCUGCUUUGAAAUGCUUGUCU"
                "GCAGAGUCACAGCAGCCAUGAAAACCUUAUGACCGUGCAAAUGAGCUCUG"
                "CUCUAAAAUUGUUGACAUUCAUGUCUCUGAGUUACAAAAGUGCUAAUUCA"
                "CUACAUGUAAUUGUGUAAGUAAACAUUGUGCCUUUACUACUUCUUUAUGU"
                "AAUAGAAGUUAUAUACCUAAGCUUAUAUAAUACAUGGGGAGGAUUAAAUA"
                "AAGGAAUAAAGAUGAAUGGACAACUCCU";
        EXPECT_STREQ(seq5, seqan::toCString((seqan::CharString)mrna_seqs[4]));
    }
}
