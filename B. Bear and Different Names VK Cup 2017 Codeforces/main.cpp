#include <bits/stdc++.h>
using namespace std;
#define ll long long
// #define ll int
#define dd double
#define vl vector<ll>
#define vvl vector<vl>
#define vd vector<dd>
#define vvd vector<vd>
#define loop ll t; cin>>t; while(t--)
#define all(a) a.begin(), a.end()
#define sz 100005
#define MOD 1000000007
#define debug cout << "here" << endl;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define ff first
#define ss second
#define pl pair<ll, ll>

ll add(ll a,ll b,ll mod){
    ll result =  (a+b)%mod;
    if(result<0){
        result+=mod;
    }
    return result;
}

ll mul(ll a,ll b,ll mod){
    ll result =  (1LL*a*b)%mod;
    if(result<0){
        result+=mod;
    }
    return result;
}

ll power(ll a, ll b, ll mod) {
    ll res = 1;
    while(b){
        if((b%2)==1){
            res=mul(res,a,mod);
        }
        a=mul(a,a,mod);
        b/=2;
    }
    return res;
}
 
ll inverse(ll x, ll p) {
    return power(x, p - 2, p);
}

class Hash {
public:
    ll length;
    const long long mod1 = 1e9 + 7, mod2 = 1e9 + 9;
    const long long p1 = 31, p2 = 37;
    vl hash1, hash2;
        
    pair<ll,ll> hash_pair;
    inline static vl inv_pow1, inv_pow2;
    inline static ll inv_size = 1;
     
    Hash() {}
 
    Hash(const string& s) {
        length = s.size();
        hash1.resize(length);
        hash2.resize(length);
 
        ll h1 = 0, h2 = 0;
        ll p_pow1 = 1, p_pow2 = 1;
        for(ll i = 0; i < length; i++) {
            h1 = add(h1,mul((s[i] - 'a' + 1),p_pow1,mod1),mod1);
            h2 = add(h2,mul((s[i] - 'a' + 1),p_pow2,mod2),mod2);
            p_pow1 = mul(p_pow1,p1,mod1);
            p_pow2 = mul(p_pow2,p2,mod2);
            hash1[i] = h1;
            hash2[i] = h2;
        }
        hash_pair = make_pair(h1, h2);
             
        inv_pow1.resize(length, -1);
        inv_pow2.resize(length, -1);
 
        inv_pow1[0]=1;
        inv_pow2[0]=1;
        
        int pw_inv1=power(p1,mod1-2,mod1);
        int pw_inv2=power(p2,mod2-2,mod2);
        
        for(ll i=1;i<length;i++){
            inv_pow1[i] = mul(inv_pow1[i - 1],pw_inv1,mod1);
            inv_pow2[i] = mul(inv_pow2[i - 1],pw_inv2,mod2);
        }
    }
 
    ll size() {
        return length;
    }
 
    pair<ll,ll> prefix(const ll index) {
        return {hash1[index], hash2[index]};
    }
 
    pair<ll,ll> substr(const ll l, const ll r) {
        if(l == 0) {
            return {hash1[r], hash2[r]};
        }
        ll temp1 = add(hash1[r],-hash1[l - 1],mod1);
        ll temp2 = add(hash2[r],-hash2[l - 1],mod2);
        temp1 = mul(temp1,inv_pow1[l],mod1);
        temp2 = mul(temp2,inv_pow2[l],mod2);
        return {temp1, temp2};
    }
 
    bool operator==(const Hash& other) {
        return (hash_pair == other.hash_pair);
    }
};

void solve(){
    ll n,k;
    cin>>n>>k;
    vector<string> str;
    
    for(ll i=0;i<26;i++){
        ll temp='A'+i;
        char ch=temp;
        string st;
        st+=ch;
        str.pb(st);
    }
    for(ll i=0;i<26;i++){
        ll temp='a'+i;
        char ch=temp;
        string st=str[i];
        st+=ch;
        str.pb(st);
        // cout<<str[i]<<" ";
    }
    
    string st;
    vector<string> ans(n," ");
    ll count=0;
    for(ll i=0;i<n-k+1;i++){
        cin>>st;
        if(ans[i]==" "){
            ans[i]=str[count];
            count++;
        }
        if(st=="NO"){
            ans[i+k-1]=ans[i];
        }
    }
    for(ll i=n-k+1;i<n;i++){
        if(ans[i]==" "){
            ans[i]=str[count];
            count++;
        }
    }
    
    for(ll i=0;i<n;i++){
        cout<<ans[i]<<" ";
    }cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // loop
    solve();

    return 0;
}
