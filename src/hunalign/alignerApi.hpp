
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <tuple>
#include "./alignerTool.cpp"
#include "./dictionary.h"


/*
((​From Steve, this is what he is looking for in the API: ))

A method that initializes the AlignerParameters and loads the Dictionary, so we do that once
A method that will align a file pair

HunAlign InitializeAligner(AlignerParams alignerParams, string dictionaryPath
{
    // dictionary should be loaded as a text file on disk – that will be clean and easy for COSMOS
    // aligner parameters can be passed in however – currently we aren’t setting any of these, so I’m not super concerned about it
}

string AlignDocumentPair(string srcFilename, string tgtFilename)
{

    // load the source lines and target lines as if they were files, do whatever hunalign does for a file pair,
    // write the lader output to stdout instead of to  file
    // ladder is the default output format
}

*/
using namespace std;
using namespace Hunglish;

namespace Hunalign {

    class HunAligner {
        protected:
            AlignParameters& alignParameters;
            string dictPath;
            DictionaryItems dictionary;

        public:
            HunAligner(AlignParameters& alignParameters, string dictPath)
            : alignParameters(alignParameters), dictPath(dictPath), dictionary(DictionaryItems()) {
                // check if the file exists
                if (!std::filesystem::exists(dictPath)) {
                    throw std::invalid_argument("Dictionary file does not exist: " + dictPath);
                }
                auto dictPathStream = std::ifstream (dictPath);
                dictionary.read(dictPathStream);
            }

            void alignDocuments(string srcFilename, string tgtFilename, string outPath="") {
                // load the source lines and target lines as if they were files, do whatever hunalign does for a file pair,
                // write the lader output to stdout instead of to  file
                // ladder is the default output format
                return alignerToolWithFilenames(
                    /*dictionary=*/this->dictionary,
                    /*huFilename=*/srcFilename,
                    /*enFilename=*/tgtFilename,
                    /*alignParameters=*/this->alignParameters,
                    /*outputFilename=*/outPath);
            }

        tuple<vector<string>, double> alignDocuments(vector<string> srcLines, vector<string> tgtLines) {

            // convert vectors to in memory streams
            auto srcStream = std::stringstream();
            for (auto& line : srcLines) {
                srcStream << line << std::endl;
            }
            SentenceList huSentenceListPretty;
            huSentenceListPretty.readNoIds( srcStream );

            auto ens = std::stringstream();
            for (auto& line : tgtLines) {
                ens << line << std::endl;
            }
            SentenceList enSentenceList;
            enSentenceList.readNoIds( ens );

            auto outStream = std::ostringstream();
            double globalQuality = alignerToolWithObjects(
                dictionary,
                huSentenceListPretty,
                enSentenceList,
                alignParameters,
                outStream);
            auto outLines = std::vector<string>{outStream.str()};
            return make_tuple(std::move(outLines), globalQuality);
        }
    };

}