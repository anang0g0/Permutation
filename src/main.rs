// y: シード値（32ビット整数）
extern crate rand;
use rand::Rng;



/*
    Fisher-Yates shuffle による方法
    配列の要素をランダムシャッフルする
*/
fn random_shuffule(mut array: [i32;8192], size:i32)-> [i32;8192]
{
    let mut _i:usize;
    let mut a:usize;
    let mut b:usize;
     let mut temp:i32;
    let mut it:i32;


    print!("{}",array[0]);
    for _i in (1..size).rev()
    {
        a = (_i - 1) as usize;
        b = rand::thread_rng().gen_range(1, _i) as usize;
        // ソートするキーの型
        temp=array[a];
        it=array[b];
        array[a]=it;
        array[b]=temp;
        //(array[a] , array[b] ) = ( array[b], array[a] )
    }
    array
}

fn main() {
    let mut a:[i32;8192]=[0;8192];
    let mut _i:usize;

    for _i in 1..10
    {
    a[_i]= rand::thread_rng().gen_range(1, 8192) as i32;
    }

    a=random_shuffule(a,8192);
    
    for _i in 1..8192{
        print!("{},",a[_i]);
    }
    println!("\n");
    println!("Hello, world!");
}
