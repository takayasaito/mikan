#include <iostream>
#include "gtest/gtest.h"
#include "test_io.hpp"
#include "mr3_core.hpp"

namespace {

    class U3007 : public TestIO
    {
    protected:
        U3007() {
            IFNAME1 = (char *)"mir_001.fasta";
            IFNAME2 = (char *)"utr3_007.fasta";
            O1FNAME1 = (char *)"test_output1_site_7.txt";
            O1FNAME2 = (char *)"test_output1_mrna_7.txt";
            O2FNAME1 = (char *)"test_output2_site_7.txt";
            O2FNAME2 = (char *)"test_output2_mrna_7.txt";
            OMPATH = (char *)"mk_miranda/";
        }

        void read_files() {
            (void)options.parseCommandLine(argc, (const char **)argv);
            coreInput.init_from_args(options);
            (void)coreInput.load_seq_from_file();
        }

        void run_main() {
            (void)mr3as::MR3CoreMain(argc, (const char **)argv);
        }

        mr3as::MR3CoreInput<mr3as::TRNATYPE> coreInput;
        mr3as::MR3Options options;
    };

    TEST_F(U3007, mrna_fasta) {
        read_files();
        mrna_ids = coreInput.get_mrna_ids();
        mrna_seqs = coreInput.get_mrna_seqs();

        EXPECT_EQ(10u, length(mrna_ids));

        const char *id1 = "hg18_refgene test1_8mer";
        EXPECT_STREQ(id1, seqan::toCString(mrna_ids[0]));

        const char *id2 = "hg18_refgene test1_8mer2";
        EXPECT_STREQ(id2, seqan::toCString(mrna_ids[1]));

        const char *id3 = "hg18_refgene test2_7mer-m8";
        EXPECT_STREQ(id3, seqan::toCString(mrna_ids[2]));

        const char *id4 = "hg18_refgene test3_7mer-a1";
        EXPECT_STREQ(id4, seqan::toCString(mrna_ids[3]));

        const char *id5 = "hg18_refgene test4_6mer1";
        EXPECT_STREQ(id5, seqan::toCString(mrna_ids[4]));

        const char *id6 = "hg18_refgene test5_6mer2";
        EXPECT_STREQ(id6, seqan::toCString(mrna_ids[5]));

        const char *id7 = "hg18_refgene test5_6mer3";
        EXPECT_STREQ(id7, seqan::toCString(mrna_ids[6]));

        const char *id8 = "hg18_refgene test5_8mer_6mer3";
        EXPECT_STREQ(id8, seqan::toCString(mrna_ids[7]));

        const char *id9 = "hg18_refgene test1_8merx4";
        EXPECT_STREQ(id9, seqan::toCString(mrna_ids[8]));

        const char *id10 = "hg18_refgene test1_8merx5";
        EXPECT_STREQ(id10, seqan::toCString(mrna_ids[9]));

        EXPECT_EQ(10u, length(mrna_seqs));
        const char *seq1 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCUGGAAAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAU"
                "UACAUUUCUGAAUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUA"
                "GAUGGAGUUUCACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUC"
                "GGCUCAGCCUCCCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCG"
                "GCUAAUGUUUGUAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGG"
                "CUGGUCUCAAACUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAA"
                "AGUGCUGGGAUGACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCU"
                "UAUACCUUCUGACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUU"
                "GGAUGUCUGUGAGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUC"
                "UCUGGGCUGAGGAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUG"
                "CUCAUGUAAUGUGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGC"
                "CACCUUGCUUGAGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCU"
                "CCCUUUCCAUGGCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGC"
                "CCAAAAGAGGUGUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGA"
                "ACAUACAAGGACAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAG"
                "GGUCUCACUCUGUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCA"
                "CUGCAACCUCCGCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCC"
                "AAGUAGCUGGGAUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUA"
                "UGUUUAGUAGAAACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACU"
                "CCUGACCUCAGGUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUA"
                "CAGGCAUGAGCCACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGA"
                "AAUAGGAAACCCCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGU"
                "GAAACUGCUGUUUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUG"
                "AUUCAACCUGAUACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGC"
                "UUUUAUGAGGAAAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAU"
                "CGGCAGCUGAACCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCA"
                "UAUGGAGCUCAUGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUG"
                "GAAGGAAACACGCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGU"
                "UGGGCUAGAUUACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUAC"
                "UUGAAUUUUUUGAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUU"
                "UUUAAAUUAAGUCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAA"
                "UCAGGAAAAGCAAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq1, seqan::toCString((seqan::CharString)mrna_seqs[0]));

        const char *seq2 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCAGU"
                "GCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCUGGAA"
                "AAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAUUACAUUUCUGAA"
                "UUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUAGAUGGAGUUUCA"
                "CUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUCGGCUCAGCCUCC"
                "CGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCGGCUAAUGUUUGU"
                "AUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGGCUGGUCUCAAAC"
                "UCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAAAGUGCUGGGAUG"
                "ACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCUUAUACCUUCUGA"
                "CAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUUGGAUGUCUGUGA"
                "GUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUCUCUGGGCUGAGG"
                "AAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUGCUCAUGUAAUGU"
                "GGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGCCACCUUGCUUGA"
                "GGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCUCCCUUUCCAUGG"
                "CAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGCCCAAAAGAGGUG"
                "UCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGAACAUACAAGGAC"
                "AUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAGGGUCUCACUCUG"
                "UCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCACUGCAACCUCCG"
                "CCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCCAAGUAGCUGGGA"
                "UUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUAUGUUUAGUAGAA"
                "ACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACUCCUGACCUCAGG"
                "UGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUACAGGCAUGAGCC"
                "ACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGAAAUAGGAAACCC"
                "CCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGUGAAACUGCUGUU"
                "UUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUGAUUCAACCUGAU"
                "ACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGCUUUUAUGAGGAA"
                "AGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAUCGGCAGCUGAAC"
                "CCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCAUAUGGAGCUCAU"
                "GUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUGGAAGGAAACACG"
                "CGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGUUGGGCUAGAUUA"
                "CAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUACUUGAAUUUUUUG"
                "AAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUUUUUAAAUUAAGU"
                "CAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAAUCAGGAAAAGCA"
                "AUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq2, seqan::toCString((seqan::CharString)mrna_seqs[1]));

        const char *seq3 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGUCUUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGUCUUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCUGGAAAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAU"
                "UACAUUUCUGAAUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUA"
                "GAUGGAGUUUCACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUC"
                "GGCUCAGCCUCCCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCG"
                "GCUAAUGUUUGUAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGG"
                "CUGGUCUCAAACUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAA"
                "AGUGCUGGGAUGACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCU"
                "UAUACCUUCUGACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUU"
                "GGAUGUCUGUGAGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUC"
                "UCUGGGCUGAGGAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUG"
                "CUCAUGUAAUGUGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGC"
                "CACCUUGCUUGAGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCU"
                "CCCUUUCCAUGGCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGC"
                "CCAAAAGAGGUGUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGA"
                "ACAUACAAGGACAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAG"
                "GGUCUCACUCUGUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCA"
                "CUGCAACCUCCGCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCC"
                "AAGUAGCUGGGAUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUA"
                "UGUUUAGUAGAAACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACU"
                "CCUGACCUCAGGUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUA"
                "CAGGCAUGAGCCACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGA"
                "AAUAGGAAACCCCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGU"
                "GAAACUGCUGUUUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUG"
                "AUUCAACCUGAUACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGC"
                "UUUUAUGAGGAAAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAU"
                "CGGCAGCUGAACCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCA"
                "UAUGGAGCUCAUGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUG"
                "GAAGGAAACACGCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGU"
                "UGGGCUAGAUUACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUAC"
                "UUGAAUUUUUUGAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUU"
                "UUUAAAUUAAGUCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAA"
                "UCAGGAAAAGCAAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq3, seqan::toCString((seqan::CharString)mrna_seqs[2]));

        const char *seq4 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAAUGUCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAAUGUCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCUGGAAAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAU"
                "UACAUUUCUGAAUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUA"
                "GAUGGAGUUUCACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUC"
                "GGCUCAGCCUCCCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCG"
                "GCUAAUGUUUGUAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGG"
                "CUGGUCUCAAACUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAA"
                "AGUGCUGGGAUGACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCU"
                "UAUACCUUCUGACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUU"
                "GGAUGUCUGUGAGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUC"
                "UCUGGGCUGAGGAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUG"
                "CUCAUGUAAUGUGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGC"
                "CACCUUGCUUGAGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCU"
                "CCCUUUCCAUGGCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGC"
                "CCAAAAGAGGUGUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGA"
                "ACAUACAAGGACAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAG"
                "GGUCUCACUCUGUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCA"
                "CUGCAACCUCCGCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCC"
                "AAGUAGCUGGGAUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUA"
                "UGUUUAGUAGAAACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACU"
                "CCUGACCUCAGGUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUA"
                "CAGGCAUGAGCCACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGA"
                "AAUAGGAAACCCCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGU"
                "GAAACUGCUGUUUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUG"
                "AUUCAACCUGAUACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGC"
                "UUUUAUGAGGAAAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAU"
                "CGGCAGCUGAACCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCA"
                "UAUGGAGCUCAUGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUG"
                "GAAGGAAACACGCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGU"
                "UGGGCUAGAUUACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUAC"
                "UUGAAUUUUUUGAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUU"
                "UUUAAAUUAAGUCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAA"
                "UCAGGAAAAGCAAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq4, seqan::toCString((seqan::CharString)mrna_seqs[3]));

        const char *seq5 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCUGGAAAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAU"
                "UACAUUUCUGAAUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUA"
                "GAUGGAGUUUCACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUC"
                "GGCUCAGCCUCCCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCG"
                "GCUAAUGUUUGUAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGG"
                "CUGGUCUCAAACUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAA"
                "AGUGCUGGGAUGACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCU"
                "UAUACCUUCUGACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUU"
                "GGAUGUCUGUGAGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUC"
                "UCUGGGCUGAGGAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUG"
                "CUCAUGUAAUGUGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGC"
                "CACCUUGCUUGAGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCU"
                "CCCUUUCCAUGGCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGC"
                "CCAAAAGAGGUGUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGA"
                "ACAUACAAGGACAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAG"
                "GGUCUCACUCUGUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCA"
                "CUGCAACCUCCGCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCC"
                "AAGUAGCUGGGAUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUA"
                "UGUUUAGUAGAAACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACU"
                "CCUGACCUCAGGUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUA"
                "CAGGCAUGAGCCACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGA"
                "AAUAGGAAACCCCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGU"
                "GAAACUGCUGUUUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUG"
                "AUUCAACCUGAUACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGC"
                "UUUUAUGAGGAAAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAU"
                "CGGCAGCUGAACCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCA"
                "UAUGGAGCUCAUGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUG"
                "GAAGGAAACACGCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGU"
                "UGGGCUAGAUUACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUAC"
                "UUGAAUUUUUUGAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUU"
                "UUUAAAUUAAGUCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAA"
                "UCAGGAAAAGCAAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq5, seqan::toCString((seqan::CharString)mrna_seqs[4]));

        const char *seq6 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGUCUGUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGUCUGUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCUGGAAAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAU"
                "UACAUUUCUGAAUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUA"
                "GAUGGAGUUUCACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUC"
                "GGCUCAGCCUCCCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCG"
                "GCUAAUGUUUGUAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGG"
                "CUGGUCUCAAACUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAA"
                "AGUGCUGGGAUGACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCU"
                "UAUACCUUCUGACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUU"
                "GGAUGUCUGUGAGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUC"
                "UCUGGGCUGAGGAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUG"
                "CUCAUGUAAUGUGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGC"
                "CACCUUGCUUGAGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCU"
                "CCCUUUCCAUGGCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGC"
                "CCAAAAGAGGUGUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGA"
                "ACAUACAAGGACAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAG"
                "GGUCUCACUCUGUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCA"
                "CUGCAACCUCCGCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCC"
                "AAGUAGCUGGGAUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUA"
                "UGUUUAGUAGAAACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACU"
                "CCUGACCUCAGGUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUA"
                "CAGGCAUGAGCCACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGA"
                "AAUAGGAAACCCCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGU"
                "GAAACUGCUGUUUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUG"
                "AUUCAACCUGAUACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGC"
                "UUUUAUGAGGAAAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAU"
                "CGGCAGCUGAACCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCA"
                "UAUGGAGCUCAUGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUG"
                "GAAGGAAACACGCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGU"
                "UGGGCUAGAUUACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUAC"
                "UUGAAUUUUUUGAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUU"
                "UUUAAAUUAAGUCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAA"
                "UCAGGAAAAGCAAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq6, seqan::toCString((seqan::CharString)mrna_seqs[5]));

        const char *seq7 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAAUGUCUUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAAUGUCUUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCUGGAAAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAU"
                "UACAUUUCUGAAUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUA"
                "GAUGGAGUUUCACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUC"
                "GGCUCAGCCUCCCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCG"
                "GCUAAUGUUUGUAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGG"
                "CUGGUCUCAAACUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAA"
                "AGUGCUGGGAUGACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCU"
                "UAUACCUUCUGACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUU"
                "GGAUGUCUGUGAGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUC"
                "UCUGGGCUGAGGAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUG"
                "CUCAUGUAAUGUGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGC"
                "CACCUUGCUUGAGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCU"
                "CCCUUUCCAUGGCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGC"
                "CCAAAAGAGGUGUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGA"
                "ACAUACAAGGACAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAG"
                "GGUCUCACUCUGUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCA"
                "CUGCAACCUCCGCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCC"
                "AAGUAGCUGGGAUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUA"
                "UGUUUAGUAGAAACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACU"
                "CCUGACCUCAGGUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUA"
                "CAGGCAUGAGCCACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGA"
                "AAUAGGAAACCCCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGU"
                "GAAACUGCUGUUUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUG"
                "AUUCAACCUGAUACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGC"
                "UUUUAUGAGGAAAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAU"
                "CGGCAGCUGAACCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCA"
                "UAUGGAGCUCAUGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUG"
                "GAAGGAAACACGCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGU"
                "UGGGCUAGAUUACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUAC"
                "UUGAAUUUUUUGAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUU"
                "UUUAAAUUAAGUCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAA"
                "UCAGGAAAAGCAAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq7, seqan::toCString((seqan::CharString)mrna_seqs[6]));

        const char *seq8 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAAUGUCUUCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCUGGAAAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAU"
                "UACAUUUCUGAAUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUA"
                "GAUGGAGUUUCACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUC"
                "GGCUCAGCCUCCCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCG"
                "GCUAAUGUUUGUAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGG"
                "CUGGUCUCAAACUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAA"
                "AGUGCUGGGAUGACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCU"
                "UAUACCUUCUGACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUU"
                "GGAUGUCUGUGAGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUC"
                "UCUGGGCUGAGGAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUG"
                "CUCAUGUAAUGUGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGC"
                "CACCUUGCUUGAGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCU"
                "CCCUUUCCAUGGCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGC"
                "CCAAAAGAGGUGUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGA"
                "ACAUACAAGGACAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAG"
                "GGUCUCACUCUGUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCA"
                "CUGCAACCUCCGCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCC"
                "AAGUAGCUGGGAUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUA"
                "UGUUUAGUAGAAACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACU"
                "CCUGACCUCAGGUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUA"
                "CAGGCAUGAGCCACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGA"
                "AAUAGGAAACCCCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGU"
                "GAAACUGCUGUUUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUG"
                "AUUCAACCUGAUACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGC"
                "UUUUAUGAGGAAAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAU"
                "CGGCAGCUGAACCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCA"
                "UAUGGAGCUCAUGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUG"
                "GAAGGAAACACGCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGU"
                "UGGGCUAGAUUACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUAC"
                "UUGAAUUUUUUGAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUU"
                "UUUAAAUUAAGUCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAA"
                "UCAGGAAAAGCAAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq8, seqan::toCString((seqan::CharString)mrna_seqs[7]));

        const char *seq9 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAG"
                "UGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAG"
                "UGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCUGGA"
                "AAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAUUACAUUUCUGA"
                "AUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUAGAUGGAGUUUC"
                "ACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUCGGCUCAGCCUC"
                "CCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCGGCUAAUGUUUG"
                "UAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGGCUGGUCUCAAA"
                "CUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAAAGUGCUGGGAU"
                "GACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCUUAUACCUUCUG"
                "ACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUUGGAUGUCUGUG"
                "AGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUCUCUGGGCUGAG"
                "GAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUGCUCAUGUAAUG"
                "UGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGCCACCUUGCUUG"
                "AGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCUCCCUUUCCAUG"
                "GCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGCCCAAAAGAGGU"
                "GUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGAACAUACAAGGA"
                "CAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAGGGUCUCACUCU"
                "GUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCACUGCAACCUCC"
                "GCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCCAAGUAGCUGGG"
                "AUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUAUGUUUAGUAGA"
                "AACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACUCCUGACCUCAG"
                "GUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUACAGGCAUGAGC"
                "CACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGAAAUAGGAAACC"
                "CCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGUGAAACUGCUGU"
                "UUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUGAUUCAACCUGA"
                "UACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGCUUUUAUGAGGA"
                "AAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAUCGGCAGCUGAA"
                "CCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCAUAUGGAGCUCA"
                "UGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUGGAAGGAAACAC"
                "GCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGUUGGGCUAGAUU"
                "ACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUACUUGAAUUUUUU"
                "GAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUUUUUAAAUUAAG"
                "UCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAAUCAGGAAAAGC"
                "AAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq9, seqan::toCString((seqan::CharString)mrna_seqs[8]));

        const char *seq10 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"
                "CCCCCCCCCAGUGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAG"
                "UGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAG"
                "UGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAG"
                "UGCCUUACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCUGGA"
                "AAAAACCUUAAAAAAUGUUUCCUCCAAAUCUGAUUUCAUUACAUUUCUGA"
                "AUUGUUGGGGUUUUUUUUGUUGUUUUGUUUUGUUUUGUAGAUGGAGUUUC"
                "ACUUUUGUUGCCCAGGCUGGAGUGUAGUGGCGCGAUCUCGGCUCAGCCUC"
                "CCGAGUAGCUGGGAUUACAGGCAUGUGCCACCACGCCCGGCUAAUGUUUG"
                "UAUUUUUAGUAGAGACGGGGUUUCACCAUGUUGGUCAGGCUGGUCUCAAA"
                "CUCCUGACCUCAGGUGAUCCGCCCACCUCAGCCUCCCAAAGUGCUGGGAU"
                "GACAGGUGUGAGCCACUGCGCCCAGCCUGAAUCAUUUCUUAUACCUUCUG"
                "ACAGCCCAACUUCCAGAGGACAGCUCUGGGGUACUCGUUGGAUGUCUGUG"
                "AGUACCUGGUCAUACGGGUCAGUAGGGAUAAGAAUUGUCUCUGGGCUGAG"
                "GAAUUCUUCUGUUCUCUGGUUUCACCAGCGUUGGGUUUGCUCAUGUAAUG"
                "UGGUCACCAUACUCAAAUGGUGUCAUGGCUGAAGUUGGCCACCUUGCUUG"
                "AGGGACAAGUUGUUUAUGUAUCAGCUCUCUGCUGGGUCUCCCUUUCCAUG"
                "GCAAAUGGGCAGCUCCAUCCUCUUGACUCUUCUAAAUGCCCAAAAGAGGU"
                "GUCAUGCUUUGGGGGUACGAUGUUUAUACUCCGUAAAGAACAUACAAGGA"
                "CAUUCACUGCUGAUUUUUUUUUUUGUUUGUUUGAGACAGGGUCUCACUCU"
                "GUCGCUCAGGCUGGAGUGCAGUGAUGCAAUCUUGGCUCACUGCAACCUCC"
                "GCCUCUCAGGUUCAAGUGGUUCUCCUUCCUCAGCCUCCCAAGUAGCUGGG"
                "AUUACAGGCACCUACCACCAGGGCCAGCUAAUUUUUGUAUGUUUAGUAGA"
                "AACGGGGUUUCACCAUGUUGGCCAGGCUGUUCUCGAACUCCUGACCUCAG"
                "GUGAUCUGCCCGCCUCGGUCUCCCAAAGUGCUGGGAUUACAGGCAUGAGC"
                "CACUGCACCUGACCUGCUGAAUUGUUUAUAAUGGCAAGAAAUAGGAAACC"
                "CCCCAAUGUCUGUUGAACAGCUAUCACGUUGAACCACGUGAAACUGCUGU"
                "UUUCUAGGCCAAAAAUGGUGAGCGAUCAUUUAUUUCAUGAUUCAACCUGA"
                "UACAUUUACAUAGUGCAAAACUGUGUCACAGUUUCAGGCUUUUAUGAGGA"
                "AAGCGUUUCUGUGUAGAAACUGGAAGCUGUUCAGGGCAUCGGCAGCUGAA"
                "CCCUGCUCCGUUGGUCAGCGUUACUAUCAUCUCGGAUCAUAUGGAGCUCA"
                "UGUCAGCCGUGUGGGUGGCGGGUGCACAGAGACGGUCUGGAAGGAAACAC"
                "GCGGAUCUGAACAGCAGUAAUCCUGGGGGAUACGGGGGUUGGGCUAGAUU"
                "ACAGAGGGCUCAUUUUCUACGUCAUGUAUUUUAUGAUACUUGAAUUUUUU"
                "GAAAUGGGCAUUUAUUUUAUAACAUGUUAAAAUGUACUUUUUAAAUUAAG"
                "UCAUUUUGUAAUAUUUGAAUUUUUACAUUUGUUGUACAAUCAGGAAAAGC"
                "AAUAAAGAUUUUUCAAAAAUAG";
        EXPECT_STREQ(seq10, seqan::toCString((seqan::CharString)mrna_seqs[9]));

    }

    TEST_F(U3007, comp_site) {
        run_main();

        gtest_compare_two_files(o1file1, o2file1);
    }

    TEST_F(U3007, comp_mrna) {
        run_main();

        gtest_compare_two_files(o1file2, o2file2);
    }
}