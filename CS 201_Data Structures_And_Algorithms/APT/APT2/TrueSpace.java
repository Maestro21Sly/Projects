public class TrueSpace {
    public long calculateSpace(int [] sizes, int clusterSize){
        long space =0;
        for (int i =0; i< sizes.length;i++){
            if (sizes[i]%clusterSize==0){
                space += sizes[i];
            }
            else{
                space += clusterSize+(sizes[i]/clusterSize)*clusterSize;
            }
        }
        return space;
        
    }
    
}
