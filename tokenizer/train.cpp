#include <sentencepiece_processor.h>
#include <sentencepiece_trainer.h>
#include <iostream>
#include <string>

int main() {
    const std::string options = 
        "--input=../data/tiny_shakespere.txt "
        "--model_prefix=m "
        "--vocab_size=2000 "                     // Increased for better coverage
        "--model_type=unigram "                  // Best for accuracy (default but explicit)
        "--character_coverage=0.9998 "           // Higher coverage for rare characters
        "--num_sub_iterations=4 "                // More EM iterations for better convergence
        "--seed_sentencepiece_size=2000000 "     // Larger seed set for better initialization
        "--shrinking_factor=0.85 "               // More conservative shrinking
        "--max_sentencepiece_length=20 "         // Allow longer pieces for better accuracy
        "--split_by_unicode_script=true "        // Better script handling
        "--split_by_number=true "                // Separate number handling
        "--normalization_rule_name=nmt_nfkc "    // Best normalization for text
        "--add_dummy_prefix=true "               // Better boundary handling
        "--remove_extra_whitespaces=true "       // Clean preprocessing
        "--hard_vocab_limit=false "              // Soft limit for better token quality
        "--num_threads=12";                       // Parallel processing
    
    try {
        sentencepiece::SentencePieceTrainer::Train(options);
        std::cout << "Training completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Training failed: " << e.what() << std::endl;
        return 1;
    }
}