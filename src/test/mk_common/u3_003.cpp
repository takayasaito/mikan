#include <iostream>
#include "gtest/gtest.h"
#include "test_fasta.hpp"

namespace {

class U3003 : public TestFasta {
protected:
    U3003() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "utr3_003.fasta";
    }
};

TEST_F(U3003, mrna_fasta) {
    read_files();
    mrna_ids = coreInput.get_mrna_ids();
    mrna_seqs = coreInput.get_mrna_seqs();

    EXPECT_EQ(1u, length(mrna_ids));

    const char *id1 = "hg18_refGene NM_018214 range=chr6:53895551-53896878 5'pad=0 3'pad=0 "
            "revComp=FALSE strand=+ repeatMasking=none";
    EXPECT_STREQ(id1, seqan::toCString(mrna_ids[0]));

    EXPECT_EQ(1u, length(mrna_seqs));
    const char *seq1 = "AGUUUCACCUCCAAGUUUUACCUCCUGUGUCUUCCUCUGCUGUCGAGACG"
            "UUCCUGUCUGCUUCCCGGGAGCCUCACGUGCUCCUUGUCCUAACCAGCCC"
            "CCGCGCGCCAUCUUCCCGUGGAGUGUGGGGAAGCUGCUGUCUCCCAGGAA"
            "GUGCCUUACUCAUCCCGCAACCAGUCAGCGCACCAGUGGUCUCCCGGUGU"
            "GAUUUUUUUUUUUUUUAAUUUCAGUUGUUUGUAAUAAGUAGAAUACACUA"
            "CUGUAAACAUACGACCUUUGUUUUUGUCUUAUGUUGGGGUAAAGGAAAGC"
            "AGGAAGGGGAAUUUUUAUCCUCCUCCCUUCCGUAAAGUGCUGGGAUAUUU"
            "UGAAUCCCCCAAGUUCCCUUGGACCUACUGAUGAGAGAUAGUUUUAUGUA"
            "UGGGGAAAAAUGGAUACUUUUUAAACCUUUUUUGGCAGCUCAGAUGGUGU"
            "AAAUUUUAAAAUUUUGUAUAGGUAUUUCAUAACAAAAAUAUGUAUUUCUU"
            "UUUUGUUAUUUUAUCUUGAAAACGGUACAUAUUUUAGUAUUUGUGCAGAA"
            "AAACAAGUCCUAAAGUAUUUGUUUUUAUUUGUACCAUCCACUUGUGCCUU"
            "ACUGUAUCCUGUGUCAUGUCCAAUCAGUUGUAAACAAUGGCAUCUUUGAA"
            "CAGUGUGAUGAGAAUAGGAAUGUGGUGUUUUAAAGCAGUGUUGCAUUUUA"
            "AUCAGUAAUCUACCUGGUGGAUUUGUUUUUAACCAAAAAGAUGAAUUAUC"
            "AAUGAUUUGUAAUUAUAUCAGUUGAUUUUUUUUGAAAAGAUGAACCAAAG"
            "GAUUUGACUGCUAAUAUUUUAUUCCUUACACUUUUUUUCUGAAUAAGUCU"
            "CUCAUAAUGAGUGCAGUGUCAGACUGUGCCUACUCUGAUGGUAUGUGCCA"
            "UUUGUAAAAUAAAAUAGAGCAGAAAAACACAAAAAGAGAACACUGGUUCA"
            "GACAUUCAGUGGGCAAGUAAAUUAUGGACUGCAAAAUAAUGAUUUUUAUU"
            "CAAGAAAGCUUUAAAAGUUUUAUAUCCAGAUAUACAACCACAAUAAAGCA"
            "AAAUAACCUACUAUCAAAAUAGAAAUGUUGCUAUCUUUAUAAGUGCAAUU"
            "UAAUUUGUAAAUAGAGUUUGAAUCAAAGUAUCACAAAAUACUGCUUCAAG"
            "AUUUAAUUUUAAAUCUGCUAAUUUAAGGGAUAUUGGGAAAAGUUUUGGUG"
            "UGUUUCUGUUGAUUUCUUUUUUGUAUGCUGUGAUAAAAGAGAAAUGAAAA"
            "GUGCCAGUCACUGUGUGGUGUCUAGGAAAAUCAUAUAUAUUUUUUUCUCC"
            "AAGAAAUAAAUUCAUCCUGGACAUUGGC";
    EXPECT_STREQ(seq1, seqan::toCString((seqan::CharString) mrna_seqs[0]));
}
}
