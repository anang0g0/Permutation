// y: シード値（32ビット整数）
extern crate rand;
use rand::Rng;

#[derive(Debug)]
struct srt {
    rand: i32,
    ind: i32,
}


// ソートするキーの型
fn SWAP(a:usize,  b:usize)-> crate::swp
    {
        let mut work;
        srp o;

        work = a; 
        a = b;           
        b = work;
        o.rand=a;
        o.ind=b;
    o
    }

/*
    Fisher-Yates shuffle による方法
    配列の要素をランダムシャッフルする
*/
fn random_shuffule(array:[i32;8192], size:i32)
{
    let mut i:usize;
    let mut a:usize;
    let mut b:usize;

    for i in (1..size).rev()
    {
        a = (i - 1) as usize;
        b = rand::thread_rng().gen_range(1, i) as usize;
        SWAP(array[a] as usize, array[b] as usize);
    }
}

fn main() {
    let a:[i32;8192];
    let mut i:i32;

    for i in 1..8192
    {
    a[i]= rand::thread_rng().gen_range(1, 8192);
    }

    random_shuffule(a,8192);
    
    for i in 1..8192{
        print!("{},",a[i]);
    }
    println!("\n");
    println!("Hello, world!");
}
