package Controllers;

/**
 * Created by artem on 27.11.16.
 */
public class WordGenerator {
    String word = null;

    public WordGenerator(String word){
        this.word = word;
    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public void increment(){
        StringBuilder builder = new StringBuilder();
        int end = word.length() - 1;
        boolean flag = true;
        while(flag){
            if(end < 0){
                builder.append('A');
                word = builder.reverse().toString();
                return;
            }else{
                if('A' == word.charAt(end)){
                    builder.append('C');
                    flag = false;
                }else if('C'== word.charAt(end)){
                    builder.append('G');
                    flag = false;
                }else if('G' == word.charAt(end)){
                    builder.append('T');
                    flag = false;
                }else if('T' == word.charAt(end)){
                    builder.append('A');
                }
                end--;
            }
        }
        for(int j = end; j >= 0; j--){
            builder.append(word.charAt(j));
        }
        word = builder.reverse().toString();
    }

    public String generateNextWord(int sizeOfIteration){
        for(int i = 0; i < sizeOfIteration; i++){
            increment();
        }
        return word;
    }

    public static void main(String[] args) {
        WordGenerator lol = new WordGenerator("AA");
        System.out.println(lol.generateNextWord(1));
    }
}
