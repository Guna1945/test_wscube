class prg1{
   public static void main(String[]args){
        for(int i=0;i<args.length;i++)
           { 
             int count=1;
             for(int j=i+1;j<args.length;j++)
             {
              if(args[i].equals(args[j]))
              {
               count++;
               args[j]=" ";
              }
           } 
            if(!args[i].equals(" ")
           {
             System.out prinln(args[i]+":"+count);
            }
        }
    }
}