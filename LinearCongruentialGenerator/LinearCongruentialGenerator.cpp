/****
 * Source: http://www.sanfoundry.com/cpp-program-implement-linear-congruential-generator-pseudo-random-number-generation/
 *
*/
#include <iostream>
     

    using namespace std;

     

    class mRND

    {

        public:

            void seed(unsigned int s)

            {

                _seed = s;

            }

     

        protected:

            mRND(unsigned int seed = 0) :

                _seed(seed), _a(0), _c(0), _m(2147483648)

            {
		cout << "m: " << _m << endl;
            }

            int rnd()

            {

                return (_seed = (_a * _seed + _c) % _m);

            }

     

            int _a, _c;

            unsigned int _m, _seed;

    };

     

    class MS_RND: public mRND

    {

        public:

            MS_RND(unsigned int seed = 0) :  mRND(seed) 

            {

                _a = 214013;

                _c = 2531011;

            }

            int rnd()

            {

                return mRND::rnd() >> 16;

            }

    };

     

    class BSD_RND: public mRND

    {

        public:

            BSD_RND(unsigned int seed = 0) :  mRND(seed)

            {

                _a = 1103515245;

                _c = 12345;

            }

            int rnd()

            {

                return mRND::rnd();

            }

    };

     

    int main(int argc, char* argv[])

    {

        BSD_RND bsd_rnd((unsigned int)std::stoul(argv[1]));

        MS_RND ms_rnd;

     
/*
        cout << "MS RAND:" << endl << "========" << endl;

        for (int x = 0; x < 10; x++)

            cout << ms_rnd.rnd() << endl;

     

        cout << endl << "BSD RAND:" << endl << "=========" << endl;

        for (int x = 0; x < 10; x++)

            cout << bsd_rnd.rnd() << endl;
*/
     
	int first = bsd_rnd.rnd();

	int repeat;

	long long count;
	
	cout << "Primeiro: " << first << endl;

	cout << "Segundo: " << bsd_rnd.rnd() << endl;	

	for(count=2; repeat != first; count++)
		repeat = bsd_rnd.rnd();
	
	cout << "Gerações até repetir: " << count << endl;

	cout << "Primeiro repetido: " << repeat << endl;

	cout << "Suposto segundo repetido: " << bsd_rnd.rnd() << endl;
	

        return 0;

    }
