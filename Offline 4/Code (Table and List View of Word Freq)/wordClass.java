package sample;

public class wordClass {
    String word;
    int freq;

    public wordClass(String word, int freq){
        this.word=word;
        this.freq=freq;
    }
    public void setWord(String word) {
        this.word = word;
    }

    public String getWord() {
        return word;
    }

    public void setFreq(int freq) {
        this.freq = freq;
    }

    public int getFreq() {
        return freq;
    }
}
