/*
    This file is a part of t18 project (C++17 framework for algotrading)
    Copyright (C) 2019, Arech (aradvert@gmail.com; https://github.com/Arech)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#include "code/percentRank.h"
#include "ma.h"

namespace t18 {

	namespace algs {

		//don't care much about performance now. Correctness and readability is the main priority.

		//code namespace contains definition of types that implements only code of an algorithm.
		//Every type in that namespace MUST NOT have any non-static members
		namespace code {
			typedef tMA_meta<percentRank> PercentRank_meta;

			struct PercentRank_call : public tMA_call_base<PercentRank_meta> {
				typedef tMA_call_base<PercentRank_meta> base_class_t;

				//defining timeseries mapping (using standard defs)
				typedef adpt_src_ht adpt_src_ht;
				typedef adpt_dest_ht adpt_dest_ht;
				typedef makeAdptDefSubstMap_t<adpt_src_ht, adpt_dest_ht> adptDefSubstMap_t;

				template<typename CallerT, typename SubstHMT = adptDefSubstMap_t>
				static void call(CallerT&& C, const bool = true) noexcept {
					constexpr auto substMap = SubstHMT();
					base_class_t::percent_rank(C.getTs(substMap[adpt_dest_ht()]), C.getTs(substMap[adpt_src_ht()])
						, base_class_t::_getLenPrm(C.getPrms()));
				}
			};
		}

		template<bool isCont, typename DVT = real_t, typename SVT = real_t, template<class> class ContTplT = TsCont_t>
		class tPercentRank : public tAlg2ts_select<isCont, tPercentRank<isCont, DVT, SVT, ContTplT>, code::PercentRank_call, DVT, SVT, ContTplT> {
		public:
			typedef tAlg2ts_select<isCont, tPercentRank<isCont, DVT, SVT, ContTplT>, code::PercentRank_call, DVT, SVT, ContTplT> base_class_t;

		public:
			template<typename... Args>
			tPercentRank(Args&&... a) : base_class_t(::std::forward<Args>(a)...) {}
		};

		typedef tPercentRank<false> PercentRank;
		typedef tPercentRank<true> PercentRank_c;

		/*template<typename DVT, typename SVT>
		class tPercentRank : public tAlg<memb::simpleAdpt<DVT, SVT>, code::PercentRank_call> {
		public:
			typedef tAlg<memb::simpleAdpt<DVT, SVT>, code::PercentRank_call> base_class_t;
			typedef tPercentRank<DVT, SVT> self_t;

			typedef typename base_class_t::srcAdpt_t srcAdpt_t;
			typedef typename base_class_t::destAdpt_t destAdpt_t;

			typedef typename base_class_t::prm_len_t prm_len_t;

		public:

			template<typename D, typename S, typename HMT, typename = ::std::enable_if_t<
				hana::is_a<hana::map_tag, HMT> && ::std::is_same_v<::std::remove_reference_t<D>, destAdpt_t>
				&& ::std::is_same_v<::std::remove_reference_t<S>, srcAdpt_t>
			>>
			tPercentRank(D&& d, S&& s, HMT&& prms) : base_class_t(pass2simpleAdpt(d, s), ::std::forward<HMT>(prms), *this) {}

			template<typename D, typename S, typename = ::std::enable_if_t<
				::std::is_same_v<::std::remove_reference_t<D>, destAdpt_t> && ::std::is_same_v<::std::remove_reference_t<S>, srcAdpt_t>
			>>
			tPercentRank(D&& d, S&& s, prm_len_t len) : base_class_t(pass2simpleAdpt(d, s), base_class_t::prms2hmap(len), *this) {}
		};

		typedef tPercentRank<real_t, real_t> PercentRank;*/

	}
}
