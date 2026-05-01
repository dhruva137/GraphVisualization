# Free / Low-Cost API Sources for "Latest Algorithm Updates"

This project can ingest algorithm updates from these sources:

## 1) arXiv API (free)
- Purpose: newest algorithm papers (graph algorithms, optimization, visualization methods).
- Endpoint pattern:
  - `http://export.arxiv.org/api/query?search_query=all:graph+algorithm&start=0&max_results=25&sortBy=submittedDate&sortOrder=descending`
- Notes:
  - No auth required.
  - Parse Atom XML and normalize into internal `AlgorithmNewsItem` records.

## 2) Crossref REST API (free)
- Purpose: metadata for publications + DOI enrichment.
- Endpoint pattern:
  - `https://api.crossref.org/works?query=graph%20algorithm&sort=published&order=desc&rows=20`
- Notes:
  - No key required (polite usage with mailto recommended).

## 3) Semantic Scholar API (free tier)
- Purpose: citation counts + trend signals.
- Endpoint pattern:
  - `https://api.semanticscholar.org/graph/v1/paper/search?query=graph%20algorithm&limit=20`
- Notes:
  - API key recommended for higher limits.

## 4) GitHub Search API (free with rate limits)
- Purpose: discover newly active/open-source implementations.
- Endpoint pattern:
  - `https://api.github.com/search/repositories?q=graph+algorithm+language:C%2B%2B&sort=updated&order=desc`
- Notes:
  - Unauthenticated is low-rate; token increases limits.

## 5) Papers With Code (community endpoints / dataset exports)
- Purpose: track SOTA tasks and algorithm families.
- Notes:
  - If official API constraints apply, ingest via periodic snapshot/export where permitted.

## Recommended ingestion policy
1. Poll every 6-24 hours depending on source rate limits.
2. Deduplicate by DOI/arXiv id/repo URL.
3. Rank updates by relevance score:
   - Recency + citation velocity + repo activity.
4. Human-review queue before showing "recommended new algorithm" in UI.

## Internal normalized shape
```json
{
  "id": "string",
  "source": "arxiv|crossref|semanticscholar|github|pwc",
  "title": "string",
  "url": "string",
  "published_at": "ISO-8601",
  "tags": ["graph", "shortest-path", "flow"],
  "score": 0.0
}
```
