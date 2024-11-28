public class FriendScore {
    public int highestScore(String[] friends) {
        int sizeOfFriendsArray = friends.length;
        int[] counter = new int[sizeOfFriendsArray];
        
        for (int i = 0; i < sizeOfFriendsArray; i++) {
            for (int j = 0; j < sizeOfFriendsArray; j++) {
                if (i == j) continue;
                if (friends[i].charAt(j) == 'Y') {
                    counter[i]++;
                } else {
                    for (int k = 0; k < sizeOfFriendsArray; k++) {
                        if (friends[i].charAt(k) == 'Y' && friends[k].charAt(j) == 'Y') {
                            counter[i]++;
                            break;
                        }
                    }
                }
            }
        }
        
        int max = 0;
        for (int i = 0; i <sizeOfFriendsArray; i++) {
            max = Math.max(max, counter[i]);
        }
        
        return max;
    }
}
