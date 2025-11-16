import { $api } from "@/lib/api/client";
import { Badge } from "@/components/ui/badge";

export default function EntitiesPage() {
  const { data, isLoading, error } = $api.useQuery("get", "/api/entities");
  if (isLoading) return <div>Loading…</div>;
  if (error) return <div>Error loading entities</div>;
  const entities = data?.entities ?? [];
  const aliases = data?.aliases ?? {};
  return (
    <div className="space-y-4">
      <h2 className="text-xl font-semibold">Entities ({entities.length})</h2>
      <div className="flex flex-wrap gap-2">
        {entities.map((e) => (
          <div key={e} className="rounded-lg border p-3 min-w-48">
            <div className="font-medium">{e}</div>
            <div className="mt-2 flex flex-wrap gap-1">
              {(aliases[e] ?? []).map((a) => (
                <Badge key={a} variant="secondary">
                  {a}
                </Badge>
              ))}
            </div>
          </div>
        ))}
      </div>
    </div>
  );
}



