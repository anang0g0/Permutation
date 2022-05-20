// y: シード値（32ビット整数）
extern crate rand;
use rand::Rng;
//use std::process::exit;


/*
    Fisher-Yates shuffle による方法
    配列の要素をランダムシャッフルする
*/
fn random_shuffule(mut array: [i32;8192], size:i32)-> [i32;8192]
{
    let mut _i:usize;
    let mut a:usize;
    let mut b:usize;


    for _i in (1..size).rev()
    {
        a = (_i ) as usize;
        b = rand::thread_rng().gen_range(1, 8192)% _i as usize;
        // ソートするキーの型
        (array[a] , array[b] ) = ( array[b], array[a] )
    }
    array
}

fn main() {
    let mut a:[i32;8192]=[0;8192];
    let mut _i:usize;

    for _i in 1..8192
    {
    a[_i]= _i as i32; 
    }
    //exit(1);
    a=random_shuffule(a,8192);
    
    for _i in 1..8192{
        print!("{},",a[_i]);
    }
    println!("\n");
    println!("Hello, world!");
}
