/*
    MapReduce library

    Copyright (C) 2009,2010,2011,2012 Craig Henderson.
    cdm.henderson@gmail.com

    Use, modification and distribution is subject to the
    Boost Software License, Version 1.0 - August 17th, 2003

    Permission is hereby granted, free of charge, to any person or organization
    obtaining a copy of the software and accompanying documentation covered by
    this license (the "Software") to use, reproduce, display, distribute,
    execute, and transmit the Software, and to prepare derivative works of the
    Software, and to permit third-parties to whom the Software is furnished to
    do so, all subject to the following:

    The copyright notices in the Software and this entire statement, including
    the above license grant, this restriction and the following disclaimer,
    must be included in all copies of the Software, in whole or in part, and
    all derivative works of the Software, unless such copies or derivative
    works are solely in the form of machine-executable object code generated by
    a source language processor.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

namespace wordcount {

struct map_task : public mapreduce::map_task<
                             std::string,                               // MapKey (filename)						--key_type
                             std::pair<char const *, char const *> >    // MapValue (memory mapped file contents)   --value_type
{
    template<typename Runtime>
    void operator()(Runtime &runtime, key_type const &/*key*/, value_type &value) const
    {
        bool in_word = false;
        char const *ptr = value.first;
        char const *end = value.second;
        char const *word = ptr;
        for (; ptr != end; ++ptr)
        {
            char const ch = std::toupper(*ptr);
            if (in_word)
            {
                if ((ch < 'A' || ch > 'Z') && ch != '\'')
                {
                    runtime.emit_intermediate(std::make_pair(word,ptr-word), 1);
                    in_word = false;
                }
            }
            else if (ch >= 'A'  &&  ch <= 'Z')
            {
                word = ptr;
                in_word = true;
            }
        }
        if (in_word)
            runtime.emit_intermediate(std::make_pair(word,ptr-word), 1);
    }
};

typedef std::pair<char const *, std::ptrdiff_t> reduce_key_t;

struct reduce_task : public mapreduce::reduce_task<
                                reduce_key_t,
                                unsigned>
{
    template<typename Runtime, typename It>
    void operator()(Runtime &runtime, key_type const &key, It it, It const ite) const
    {
        runtime.emit(key, std::accumulate(it, ite, 0));
    }
};

class combiner
{
  public:
    template<typename IntermediateStore>
    static void run(IntermediateStore &intermediate_store)
    {
        combiner instance;
        intermediate_store.combine(instance);
    }

    void start(reduce_task::key_type const &)
    {
        total_ = 0;
    }

    template<typename IntermediateStore>
    void finish(reduce_task::key_type const &key, IntermediateStore &intermediate_store)
    {
        if (total_ > 0)
            intermediate_store.insert(key, total_);
    }

    void operator()(reduce_task::value_type const &value)
    {
        total_ += value;
    }
        
  private:
    combiner() { }

  private:
    unsigned total_;
};

typedef
mapreduce::job<
    wordcount::map_task
  , wordcount::reduce_task
  , wordcount::combiner
> job;

}   // namespace wordcount
