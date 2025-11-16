import { $api } from "../lib/api/client";

export default function Dashboard() {
  const { data, isLoading, error } = $api.useQuery("get", "/api/index");
  if (isLoading) return <div>Loading…</div>;
  if (error || !data) return <div>Error loading index</div>;
  const s = data.stats;
  return (
    <div className="grid grid-cols-2 md:grid-cols-5 gap-3">
      <Stat label="Beats" value={s.beats} />
      <Stat label="Facts" value={s.facts} />
      <Stat label="Timeline" value={s.timeline_events} />
      <Stat label="Consistency" value={s.consistency_entries} />
      <Stat label="Entities" value={s.entities_tracked} />
    </div>
  );
}

function Stat({ label, value }: { label: string; value: number }) {
  return (
    <div className="rounded-lg border p-4">
      <div className="text-xs text-muted-foreground">{label}</div>
      <div className="text-2xl font-semibold">{value}</div>
    </div>
  );
}



