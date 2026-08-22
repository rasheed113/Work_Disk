import { Search } from '../../components/input/Search'

export function SearchCard({ value, onChange }: { value: string; onChange: (value: string) => void }) {
  return (
    <section className="wd-dashboard-search-card" aria-label="Dashboard search">
      <div className="wd-dashboard-search-card__icon" aria-hidden="true">🔎</div>
      <div className="wd-dashboard-search-card__field">
        <Search value={value} onChange={onChange} placeholder="Search Dashboard..." />
      </div>
    </section>
  )
}
