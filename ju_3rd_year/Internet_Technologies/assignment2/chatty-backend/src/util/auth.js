
const { connections , users} = require("../db");

const bcrypt = require('bcrypt');
const saltRounds = 10;

var user_num =1;
const signupUser = async (user) => {


    
    if ( Object.keys(users).indexOf(user.username) > -1 ){
        return {
            error : true,
            message : 'username exists'
        }
    }
    
    // bcrypt.genSalt( saltRounds , function(err, salt){
        // if (err){
        //     console.log('signup failed in forming hash');
        //     return {
        //         error : true,
        //         message : 'signup failed'
        //     }
        // }
        
    //     bcrypt.hash( user.password ,salt, async function(err,hash){
    //         if (err){
    //             console.log('signup failed in forming hash');
    //             return {
    //                 error : true,
    //                 message : 'signup failed'
    //             }
    //         }
            
    //         users[user.username] = {
    //             name : user.name,
    //             username : user.username, 
    //             password : hash,
    //             avatar : `https://i.pravatar.cc/150?img=${user_num}`,
    //         }
    //         user_num += 1;
    //         console.log('inside bcrypt');
    //         message= {
    //                 error:false, 
    //                 message : 'signup successful',
    //                 user : {
    //                     name : user.name,
    //                     username : user.username, 
    //                     avatar :users[user.username].avatar
    //                 }
    //             }
    //     })
    // })

    const genSalt = await new Promise((resolve, reject) => {
        bcrypt.genSalt( saltRounds , function(err, salt){
            if (err){
            console.log('signup failed in forming hash');
            reject(err);
            }
            resolve(salt);
        })
    });

    // hash(abcd + 87493sds) = res_hash

    const hash = await bcrypt.hash( user.password ,genSalt );

    users[user.username] = {
        name : user.name,
        username : user.username, 
        password : hash,
        avatar : `https://i.pravatar.cc/150?img=${user_num}`,
    }
    user_num += 1;

    return {
            error:false, 
            message : 'signup successful',
            user : {
                name : user.name,
                username : user.username, 
                avatar :users[user.username].avatar
            }
    }





  }


  // hash(abcd + 9749) === 

    

const loginUser = async ( user ) => {
    var index = Object.keys(users).indexOf(user.username);

    if ( index > -1 ){
        
        const match = await bcrypt.compare( user.password ,users[user.username].password );
        if ( match ){
            return {
                error : false,
                message : 'logged in successfully'
            }
        }
        else{
            return {
                error :true, 
                message : 'Password incorrect'
            }
        }
    }
    else{ 
        return  {
            error : true ,
            message : 'Username not found'
        }

    }
}


module.exports= {
    signupUser: signupUser, 
    loginUser: loginUser
};