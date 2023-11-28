import nltk
from nltk.corpus import wordnet
import json
import sys

nltk.download('wordnet')

def get_synonyms(word):
    synonyms = []
    for syn in wordnet.synsets(word):
        for lemma in syn.lemmas():
            synonyms.append(lemma.name())
    return list(set(synonyms))

def find_synonyms(words):
    results = {}
    for word in words:
        lemmatized_word = wordnet.morphy(word) or word
        synonyms = get_synonyms(lemmatized_word)
        results[word] = {"original_word": lemmatized_word, "synonyms": synonyms}
    return json.dumps(results)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python lemmatize_and_synonyms.py word1 word2 ...")
        sys.exit(1)

    words_to_find_synonyms_for = sys.argv[1:]
    synonyms_results = find_synonyms(words_to_find_synonyms_for)

    print(synonyms_results)
