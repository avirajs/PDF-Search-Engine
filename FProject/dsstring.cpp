#include "dsstring.h"
#include <vector>
#include <iomanip>

using namespace std;


String::String()
{
    //set default arguments for the String class
    carr = nullptr;
    sizearr = 0;

}

String::String(const char*a)
{
    //check to see if the char* is a null pointer
   if(a != nullptr)
   {
       //get the size of the char*, and use it to fill in the char array for the class
        sizearr = strlen(a);
        carr = new char[sizearr +1];
        for(int i = 0; i < sizearr; i++)
        {
            carr[i] = a[i];
        }
        //end the char array with a null terminator
        carr[sizearr] = '\0';
   }
   else
   {
       //set array to null pointer
        carr = nullptr;
        sizearr = 0;
   }
}

String::String(const String&a)
{
    //check to see if the String is a null pointer
    if(a.carr != nullptr)
    {
        //get the size of the String, and use it to fill in the char array for the class
        sizearr = a.sizearr;
        carr = new char[sizearr+1];
        for (int i=0; i < sizearr; i++)
        {
            carr[i] = a.carr[i];
        }
        //end the char array with a null terminator
        carr[sizearr] = '\0';
    }

}

String& String::operator= (const String&a)
{
    // makes sure the arrays are different before assignment
    if (&a != this)
    {
        //get the size of the String
        sizearr = a.sizearr;
        //reset String to null
        if (carr != nullptr)
        {
            delete [] carr;
        }
            carr = new char[sizearr];
        //populate the String
        for (int i=0; i < sizearr; i++)
        {
            carr[i]= a.carr[i];
        }
    }
    //returns newly created String
    return *this;
}

 String& String::operator= (const char*a)
 {
    // makes sure the arrays are different before assignment
     if (a != carr)
     {
         int k = strlen(a);
         //checks to see if the lengths are equal, and resizes the string to populate
         if (sizearr != k)
         {
             delete [] carr;
             sizearr = strlen(a);
             carr = new char[sizearr];
         }
         //populates the String
         for (int i=0; i < sizearr; i++)
         {
             carr[i]=a[i];
         }
     }
     return *this;

 }

 String String::operator+ (const String&a)
 {
    //sets new size of String
    int addArr = sizearr + a.sizearr;
    char* c;
    int k;
    //sets new array for the String
    c = new char[addArr+1];
    //populates the String
    for (int i=0; i < addArr; i++)
    {
         if(i < sizearr)
        {
             c[i] = carr[i];
        }
        else
        {
            k = i - sizearr;
            c[i] = a.carr[k];
        }
     }
    //puts null terminator at the end
    c[addArr] = '\0';
    //returns newly created String
    return String(c);
 }

 bool String::operator== (const char*a)
 {
     //checks to see if String and char* have same length
    int k = strlen(a);
    if (sizearr != k)
    {
        return false;
    }
    //checks each element indivdually
    for (int i = 0; i < sizearr; i++)
    {
        if (carr[i] != a[i])
        {
            return false;
        }
    }
    return true;
 }

 bool String::operator== (const String&a)
 {
    //checks to see if Strings have same length
     if (sizearr != a.sizearr)
     {
         return false;
     }
    //checks each element indivdually
     for (int i =0; i < sizearr; i++)
     {
         if (carr[i] != a.carr[i])
         {
             return false;
         }
     }
     return true;
 }

bool String::operator> (const String&a)
{
    int num1;
    int num2;
    char c;
    char d;
    //checks to see which String is larger
    if (a.sizearr > sizearr)
    {
        //checks all elements of smaller String
        for (int i = 0; i < sizearr; i++)
        {
             //compares each element to determine which one is larger
            c = carr[i];
            d = a.carr[i];
            num1 = (int)c;
            num2 = (int)d;

        if (num1 > num2)
        {
            return true;
        }
        if (num2 > num1)
        {
            return false;
        }
        }
        return true;
    }
    //checks to see which String is larger
    else if (sizearr > a.sizearr)
    {
      //checks all elements of smaller String
      for (int i = 0; i < a.sizearr; i++)
      {
          //compares each element to determine which one is larger
        c = carr[i];
        d = a.carr[i];
        num1 = (int)c;
        num2 = (int)d;
        if (num1 > num2)
        {
            return true;
        }
        if (num2 > num1)
        {
            return false;
        }
      }
      return true;
    }
    else
    {
        //if the Strings are the same size
        for (int i = 0; i < sizearr; i++)
        {
            //compares each element to determine which one is larger
          c = carr[i];
          d = a.carr[i];
          num1 = (int)c;
          num2 = (int)d;
          if (num1 > num2)
          {
              return true;
          }
          if (num2 > num1)
          {
              return false;
          }
        }
        return false;
    }
}

char& String::operator[] (const int a)
{
    //checks to see if String is a null pointer
    if ( carr != nullptr)
    {
        //checks to see if subscript is negaative
        if ( a < 0 )
        {
            //returns correct element if negative
                return carr[sizearr+a];
        }
    }
    //returns  correct element
    return carr[a];

}

int String::size()
{
    //returns size of the String
    return sizearr;
}

String String::substring(int a, int b)
{
    char* c;
    //checks to see if first subscript is 0 and second is positive
    if (a == 0 && b > 0)
    {
        //populates new char* with correct elements
        c = new char[b+1];
        for (int i =0; i < b; i++)
        {
            c[i] = carr[i];
        }
        //puts null terminator at the end
        c[b] = '\0';
    }
    //checks to see if a is negative nd if a is less than b
    else if (a < 0 && a < b)
    {
         //populates new char* with correct elements
        c = new char[sizearr+a +1];
        for (int k = 1 + (sizearr+a); k < (sizearr+b)+1; k++)
        {
            c[k-(1 + (sizearr+a)) ] = carr[k];
        }
        //puts null terminator at the end
        c[sizearr+a] = '\0';
    }
    else
    {
        int h = 0;
        h = sizearr+b+1;
        c = new char[h];
        //populates new char* with correct elements
        for (int k = a; k < (sizearr+b)+2; k++)
        {
            c[k] = carr[k];
        }
        //puts null terminator at the end
        c[h] = '\0';
     }
    //returns the new String
    return String(c);


}

char* String::c_str()
{

    //creates a char* to hold String elements
      char* p = new char[sizearr+1];
      //populates the char* with each element
      for (int i =0; i < sizearr; i++)
      {
          p[i] = carr[i];
      }
      //puts null terminator at the end
      p[sizearr] = '\0';
      //deallocates old carr
      delete [] carr;
      //sets carr equal to the new char array
      carr = p;
      //returns the char*
      return carr;
}

ostream& operator<< (std::ostream&o, const String&a)
{
    //checks to see if the String is null
    if (a.carr != nullptr)
    {
    //outputs each element of the String
    for (int i = 0; i < a.sizearr; i++ )
    {
        o << a.carr[i];
    }
    }
    else
    {
        //outputs null
        o << "" << endl;
    }
    //returns the output
    return o;

}

String::~String()
{   //checks to see if the char* is null
    if ( carr != nullptr)
    {
    //deletes the char* when running is finished
    delete [] carr;
    }
}
