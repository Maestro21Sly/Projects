//package APT.APT3 ;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class MemberCheck {
    public String [] whosDishonest(String[] club1, String [] club2, String [] club3){
        Set <String> club1Set= new HashSet<>();
        for(int i =0;i < club1.length;i++){
            if (!club1Set.contains(club1[i])){
                club1Set.add(club1[i]);
            }   
        }
        Set<String> club2Set = new HashSet<>();
        for (int s =0; s< club2.length;s++){
            if (!club2Set.contains(club2[s])){
                club2Set.add(club2[s]);
            } 
        }
        Set<String> club3Set = new HashSet<>();
        for(int t=0; t< club3.length;t++){
            if (!club3Set.contains(club3[t])){
                club3Set.add(club3[t]);
            } 
        }
        Set<String> dishonestMembers1and2 = new HashSet<>(club1Set);
        dishonestMembers1and2.retainAll(club2Set);

        Set<String> dishonestMembers1and3 = new HashSet<>(club1Set);
        dishonestMembers1and3.retainAll(club3Set);

        Set<String> dishonestMembers2and3 = new HashSet<>(club2Set);
        dishonestMembers2and3.retainAll(club3Set);

        HashSet<String> dishonestMembers = new HashSet<>();
        dishonestMembers.addAll(dishonestMembers1and2);
        dishonestMembers.addAll(dishonestMembers1and3);
        dishonestMembers.addAll(dishonestMembers2and3);

        String[] dishonestMembersArray = dishonestMembers.toArray(new String[dishonestMembers.size()]);
        Arrays.sort(dishonestMembersArray);

        return dishonestMembersArray;
    }
    
}
