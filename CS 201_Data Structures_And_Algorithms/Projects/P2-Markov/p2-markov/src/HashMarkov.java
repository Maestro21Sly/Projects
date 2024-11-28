import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Random;

public class HashMarkov implements MarkovInterface {
    protected String[] myWords;		// Training text split into array of words 
	protected Random myRandom;		// Random number generator
	protected int myOrder;			// Length of WordGrams used
    protected HashMap<WordGram, List<String>> originalMap; //creating an instance variable for a HashMap
	protected static String END_OF_TEXT = "*** ERROR ***"; 

    public HashMarkov(int order){
        myOrder = order;
        myRandom = new Random();
        originalMap = new HashMap<>();
    }
    

    @Override
    public void setTraining(String text) {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'setTraining'");
        myWords = text.split("\\s+");
        originalMap.clear();
        WordGram nowKey = new WordGram(myWords, 0, myOrder);
        WordGram nowWg = new WordGram(myWords, 0, myOrder);
        for (int j = nowKey.length(); j< myWords.length; j++){
            String nowWord = myWords[j];
            originalMap.putIfAbsent(nowWg,new ArrayList<String>());

            originalMap.get(nowWg).add(nowWord);
            nowWg = nowWg.shiftAdd(nowWord);

        }
    }

    @Override
    public List<String> getFollows(WordGram wgram) {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'getFollows'");
        List<String> emptypage = new ArrayList<>();
        if (originalMap.containsKey(wgram)){
            return originalMap.get(wgram);
        }
        else{
            return emptypage;
        }
        
    }
    /**
	 * Returns a random word that follows kGram in the training text.
	 * In case no word follows kGram, returns END_OF_TEXT
	 * @param wgram is being searched for in training text. Typically
	 * the previous words of the randomly generated text, but could be
	 * an arbitrary WordGram.
	 * @return a random word among those that follow after kGram in 
	 * the training text, or END_OF_TEXT if none
	 */
	private String getNextWord(WordGram wgram) {
		List<String> follows = getFollows(wgram);
		if (follows.size() == 0) {
			return END_OF_TEXT;
		}
		else {
			int randomIndex = myRandom.nextInt(follows.size());
			return follows.get(randomIndex);
		}
	}

    @Override
    public String getRandomText(int length) {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'getRandomText'");
        ArrayList<String> randomWords = new ArrayList<>(length);
		int index = myRandom.nextInt(myWords.length - myOrder + 1);
		WordGram current = new WordGram(myWords,index,myOrder);
		randomWords.add(current.toString());

		for(int k=0; k < length-myOrder; k += 1) {
			String nextWord = getNextWord(current);
			if (nextWord.equals(END_OF_TEXT)) {
				break;
			}
			randomWords.add(nextWord);
			current = current.shiftAdd(nextWord);
		}
		return String.join(" ", randomWords);
	}

    @Override
    public int getOrder() {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'getOrder'");
        return myOrder;
    }

    @Override
    public void setSeed(long seed) {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'setSeed'");
        myRandom.setSeed(seed);
    }
    
}
