create()
{
    echo Enter the address book name
    read name
    
    check=`ls | grep $name | wc -w`
    
    if [ $check -gt 0 ]
    then
       echo error:address book is already exit
    else
       touch $name
       echo address book is created
    fi
}
display()
{
    echo Enter the address book name to display
    read name
    
    check=`ls | grep $name | wc -w`
    
    if [ $check -gt 0 ]
    then
       echo -------$name file data-------
       cat $name
    else
       echo address book is not existing
    fi
}
Insert()
{
    echo Enter the address book name
    read name
    
    check=`ls | grep $name | wc -w`
    
    if [ $check -gt 0 ]
    then
       echo Enter Email 
       read email
       
       len=`cat $name | grep $email | wc -w`
       if [ $len -gt 0 ]
       then
           echo Email is already exit
       else
           echo Enter fisrtname lastname mobileno
           read firstname lastname moblieno
           
           record=`echo $firstname $lastname $moblieno $email`
           echo $record >> $name
           echo "record Insereed"
       fi
       
    else
       echo error:address book not found!
    fi
}
while [ true ]
do
    echo ************MENU****************
    echo 1.Create
    echo 2.display
    echo 3.Insert
    
    echo 6.Exit
    
    echo Enter your choice
    read choice
    
    case $choice in
        
        1)  create ;;
        
        2)  display ;;
        
        3)  Insert ;;
        
        6)  echo Thank you
            exit  ;;
        
        *) echo Enter  correct choice 
    esac

done
